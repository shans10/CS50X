// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <strings.h>   // For strcasecmp function
#include <string.h>    // For strlen function
#include <stdlib.h>    // For malloc and free functions
#include <ctype.h>     // For tolower function
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table. This number is calculated by using the max case in my hash function i.e. word consisting of 45 'z' + 1
// since index starts from 0
const unsigned int N = 124954;

// Hash table initialized to NULL
node *table[N] = {NULL};

// Number of words loaded
unsigned int loaded_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Length of the current word +1 extra space for null character
    int len = strlen(word) + 1;
    // Copy of current word with all lowercase letters
    char word_lower[len];

    // Converting all letters of current word to lowercase and copying it to new array
    for (int i = 0; i < len; i++)
    {
        word_lower[i] = tolower(word[i]);
    }

    // Since all words in dictionary are lower case so the hash is also calculated based on that, that is why lowercase copy of word is used.
    int index = hash(word_lower);

    // Creating a temporary pointer to node and is initialized to the start of calculated hash index
    node *temp = table[index];

    // Checks if the word exists at the dtermined location
    while (temp != NULL)
    {
        if (strcasecmp(temp -> word, word) == 0)
        {
            return true;
        }
        temp = temp -> next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int index = 0;
    // If word is not NULL then the index is calculated
    if (word != NULL)
    {
        for (int i = 0, l = strlen(word); i < l; i++)
        {
            // This is my own hash function any resemblance to others is only coincidental
            index = index + ((int)word[i] * (i + 1)); // Ascii value of all the characters in the string is multiplied by their corresponding
            // index + 1 and added together
        }
        return (index - 97); // 97 is substracted from calculated value so that in case of single char words indexing starts from 0
    }

    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open the dictionary file in read only mode
    FILE *f = fopen(dictionary, "r");

    // Return false if unable to load file
    if (!f)
    {
        return false;
    }

    // Creating a char array with max length of a word
    char word[LENGTH + 1];

    // Reading the file word by word and storing in hash table until the fscanf function returns EOF
    while (fscanf(f, "%s", word) != EOF)
    {
        // Creating a new node
        node *new_node = malloc(sizeof(struct node));

        // Copying the current word read from dictionary to the node
        strcpy(new_node -> word, word);

        // Determining the position of the word in the hash table
        int index = hash(word);

        // If there is no collision then new node is directly added to hash table
        if (table[index] != NULL)
        {
            new_node -> next = table[index];
            table[index] = new_node;
        }

        // If collision occurs linked list is formed and the new node becomes the first node in the linked list
        else
        {
            table[index] = new_node;
            new_node -> next = NULL;
        }
        // Counting the number of words loaded
        loaded_words++;
    }

    // Closing the dictionary file
    fclose(f);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return loaded_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Freeing the memory means the whole table node pointer array points to NULL so itearating through the whole array to make it NULL
    for (int i = 0; i < N; i++)
    {
        // Iterating throung the whole linked list pointed by the table[i] pointer and freeing each node
        while (table[i] != NULL)
        {
            node *tmp = table[i];          // Ctreating a temporary node that points to the current value to table[i] pointer
            table[i] = table[i] -> next;   // Changing the value of table[i] to point to the next node in the linked list
            free(tmp);                     // Freeing the previous node
        }
    }

    return true;
}
