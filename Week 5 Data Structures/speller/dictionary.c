// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 1000;
int counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hashing word for the hash value
    int index = hash(word);

    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) != 0)
        {
            cursor = cursor->next;
        }
        else
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improved hash function
    int points = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        points += toupper(word[i]) - 'A';
    }
    return points % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];

    // Read strings from file one at a time
    while (fscanf(file, "%s", word) != EOF)
    {
        // New node for each word
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next = NULL;

        // Hash word to obtain a hash value
        int index = hash(word);

        // Insert node into hash table in the corresponding bucket
        n->next = table[index];
        table[index] = n;
        counter++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through the buckets of the hash table
    for (int i = 0; i < N; i++)
    {
        // Cursor to move through the linked list
        node *cursor = table[i];

        // Free the allocated memory for its nodes
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
