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
const unsigned int N = 690;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int idx = hash(word);
    node *ptr = table[idx];
    while (ptr != NULL)
    {
        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }

        ptr = ptr->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int len = 0;
    for (int i = 0, n = strlen(word); i <= n; i++)
    {
        char c = toupper(word[0]);
        len += c - 'A';
    }
    return len;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Opens dictionary and cheks for errors with fopen
    FILE *dict = fopen(dictionary, "r");
    if (dict != NULL)
    {
        // creates buffer for word of size LENGTH
        char buffer[LENGTH + 1];

        // loads each word into buffer until end of file is reached
        while (fscanf(dict, "%s", buffer) != EOF)
        {
            // alocates memory for new node and checks for errors with malloc
            node *new = malloc(sizeof(node));
            if (new == NULL)
            {
                fclose(dict);
                return false;
            }

            // copies the word from buffer into node
            strcpy(new->word, buffer);

            // sets next pointer to NULL
            new->next = NULL;

            // passing the word to hash function to determine where the word should go in the hash table
            unsigned int idx = hash(new->word);

            // add node to linked list in table[x] place of hash table
            new->next = table[idx];
            table[idx] = new;
        }

        fclose(dict);
        return true;
    }

    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    long wrdcount = 0;

    for (int i = 0; i <= N; i++)
    {
        node *ptr = table[i];

        while (ptr != NULL)
        {
            wrdcount++;
            ptr = ptr->next;
        }
    }
    return wrdcount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i <= N; i++)
    {
        node *ptr = table[i];

        while (ptr != NULL)
        {
            node *tmp = ptr->next;
            free(ptr);
            ptr = tmp;
        }

        // successfuly freed all alocated memory
        if (i == N)
        {
            return true;
        }
    }

    return false;
}
