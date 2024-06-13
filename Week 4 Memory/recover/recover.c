#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check for proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open memory card
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Buffer for pointing to where to store the read data
    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];

    // Counter for JPEGs founded
    int counter = 0;

    // Allocate bytes for the name of the file
    char *filename = malloc(8 * sizeof(char));

    // Output file
    FILE *output = NULL;

    // Loop for data to read every block of 512 bytes into a buffer
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            // If it's the first JPEG
            if (counter == 0)
            {
                sprintf(filename, "%03i.jpg", counter);
                output = fopen(filename, "wb"); // Using "wb" mode for writing in binary
                fwrite(buffer, 1, BLOCK_SIZE, output);
                counter++;
            }
            // If already found a JPEG
            else if (counter > 0)
            {
                // Open a new file to continue writing
                fclose(output);
                sprintf(filename, "%03i.jpg", counter);
                output = fopen(filename, "wb"); // Using "wb" mode for writing in binary
                fwrite(buffer, 1, BLOCK_SIZE, output);
                counter++;
            }
        }
        // If it's not the start of a new JPEG
        else if (counter > 0)
        {
            // continue writing to it, for the next 512 bytes block of the current JPEG
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }
    }

    // Close files
    free(filename);
    fclose(file);
    fclose(output);
}
