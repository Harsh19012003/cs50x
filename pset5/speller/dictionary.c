 // Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
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

// Number of buckets in hash table
const unsigned int N = 50000;

// Hash table
node *table[N];

// Global variable of size of dictionary
unsigned int dict_size;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Generate hash_value for word
    unsigned int hash_value = hash(word);

    // Check for word in hash table at hash value
    node *trav = table[hash_value];
    if (trav == NULL)
    {
        return false;
    }

    while (true)
    {
        if (strcasecmp(word, trav->word) == 0)
        {
            return true;
        }
        else
        {
            trav = trav->next;
            if (trav == NULL)
            {
                return false;
            }
        }
    }
    return false;
}

// Hashes word to a number
/***********************************************************************************************/
// CITE
/*github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
A case-insensitive implementation of the djb2 hash function.
http:stackoverflow.com/questions/2571683/djb2-hash-function.*/

/************************************************************************************************/
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;

    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Variables
    unsigned int bytes_read, hash_value;
    char *w = malloc(LENGTH + 1);
    if (w == NULL)
    {
        return false;
    }

    // Set all pointer of hash table to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // File open
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Dictionary cannot be loaded in dictionary.c\n");
        return false;
    }

    while (true)
    {
        // Read a word from file at a time
        bytes_read = fscanf(dict, "%s", w);
        if (bytes_read == EOF)
        {
            break;
        }

        // Get hash_value using hash function
        hash_value = hash(w);

        //Creat new node and link it to hash-table
        node *temp = malloc(sizeof(node));
        if (temp == NULL)
        {
            return false;
        }

        strcpy(temp->word, w);
        temp->next = NULL;

        if (table[hash_value] == NULL)
        {
            table[hash_value] = temp;
            dict_size++;
        }
        else
        {
            temp->next = table[hash_value];
            table[hash_value] = temp;
            dict_size++;
        }
    }

    fclose(dict);
    free(w);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Size already determined while loading hash-table
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Declaring two pointers
    node *temp1, *temp2;
    unsigned int unload_size = 0;

    for (int i = 0; i < N; i++)
    {
        temp1 = temp2 = table[i];
        if (temp1 == NULL || temp2 == NULL)
        {
            continue;
        }

        while (true)
        {
            temp2 = temp2->next;
            {
                if (temp2 == NULL)
                {
                    free(temp1);
                    unload_size++;
                    break;
                }
            }
            free(temp1);
            unload_size++;
            temp1 = temp2;
        }
    }

    // Cross-check for load and unload size
    if (dict_size == unload_size)
    {
        return true;
    }
    return false;
}