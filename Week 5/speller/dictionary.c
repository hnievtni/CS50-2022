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
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int HASHTABLE_SIZE = 100000;
int word_count = 0;

// Hash table
node *hashtable[HASHTABLE_SIZE];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_index = hash(word);
    node *new_node = hashtable[hash_index];

    while (new_node != NULL)
    {
        if (strcasecmp(word, new_node->word) == 0)
        {
            return true;
        }
        new_node = new_node->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_sum = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        hash_sum += tolower(word[i]);
    }
    return hash_sum % HASHTABLE_SIZE;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        strcpy(new_node->word, word);

        // Initializes & calculates index of word for insertion into hashtable
        int hash_index = hash(word);

        // Initializes head to point to hashtable index/bucket
        new_node->next = hashtable[hash_index];
        hashtable[hash_index] = new_node;
        word_count++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        // Assign cursor
        node *new_node = hashtable[i];
        // Loop through linked list
        while (new_node != NULL)
        {
            // Make temp equal cursor;
            node *temp = new_node;
            // Point cursor to next element
            new_node = new_node->next;
            // free temp
            free(temp);
        }
        if (new_node == NULL && i == HASHTABLE_SIZE - 1)
        {
            return true;
        }
    }
    return false;
}
