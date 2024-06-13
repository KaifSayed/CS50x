#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get user input for blocks height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    for (int i = 1; i <= height; i++)
    {
        // Print spaces
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }
        // Print left blocks
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        // Print spaces
        printf("  ");
        // Print right blocks
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
