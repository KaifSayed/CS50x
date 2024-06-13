#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool isValidKey(string key);
void encrypt(string plaintext, string key);

int main(int argc, string argv[])
{
    // Check if the correct number of command-line arguments is provided
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Get the key from the command-line argument
    string key = argv[1];

    // Check if the key is valid
    if (!isValidKey(key))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Get plaintext from the user
    string plaintext = get_string("plaintext: ");

    // Encrypt and print the ciphertext
    encrypt(plaintext, key);

    return 0;
}
bool isValidKey(string key)
{
    // Check if the key is exactly 26 characters long
    if (strlen(key) != 26)
    {
        return false;
    }
    // Check if each character in the key is alphabetic and occurs exactly once
    int count[26] = {0};
    for (int i = 0; i < 26; i++)
    {
        char c = toupper(key[i]);
        if (!isalpha(c) || count[c - 'A'] > 0)
        {
            return false;
        }
        count[c - 'A']++;
    }
    return true;
}
void encrypt(string plaintext, string key)
{
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        char c = plaintext[i];
        // Encrypt only alphabetical characters, preserving case
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            printf("%c", isupper(c) ? toupper(key[c - base]) : tolower(key[c - base]));
        }
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
}
