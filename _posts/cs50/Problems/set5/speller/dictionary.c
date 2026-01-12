// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>  // 需要这个头文件来使用 strcasecmp
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
// const unsigned int N = 26;
// const unsigned int N = 676; // 26 * 26;
const unsigned int N = 100000;
// Hash table
node *table[N];
// Word count
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // 使用 strcasecmp 进行大小写不敏感比较
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
    // djb2 算法：初始值 5381，乘数 33
    unsigned long hash = 5381;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = ((hash << 5) + hash) + tolower(word[i]);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    // Create a buffer to read file
    char word[LENGTH+1];
    // Loop for load each word from file
    while (fscanf(file, "%s", word) != EOF)
    {
        // malloc memory for node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            unload();
            return false;
        }
        strcpy(new_node->word, word);
        unsigned int index = hash(word);
        new_node->next = table[index];
        table[index] = new_node;
        word_count++;
    }
    // Close the dictionary file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
