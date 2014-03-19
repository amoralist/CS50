/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

// Inclusions and definitions
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// nearest prime > 10% of number of entries
#define TABLE_SIZE 14321
#define MAX_LEN 45

// Type and Function Declarations
typedef struct node {
    char word[LENGTH + 1];
    struct node* next;
}node;

typedef struct {
    int count;
    node* buckets[TABLE_SIZE];
}dictionary;

void clearList(node** head);
unsigned int hash(char* string, int max);

// Global access to a dictionary 'object'.
dictionary* dict = NULL;

/* Check: Checks for a word's inclusion in a dictionary
 * Returns True if word is in dictionary else False. */
bool check(const char* word) {
		// TODO
    return true;
}

/* Load: Loads dictionary into memory.  
 *    Returns true if successful else false. */

bool load(const char* dictionary) {
    // attempt to open dictionary passed in speller.c 
    FILE* dict_f = fopen("dictionary.txt", "r");
    if (dict_f == NULL) {
        printf("Could not load dictionary.\n");
        return false;
    }
    
    // allocate memory for overall dictionary structure
        // and initialize it 
    dict = malloc(sizeof(dictionary));
    dict->count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        dict->buckets[i] = NULL;
    }

    // iterate through dictionary file, create nodes and enter
        // into proper hash buckets 
    while (feof(dict_f) == 0) {
        node* new_node = malloc(sizeof(node));
        fscanf(dict_f, "%s", new_node->word);
        if (ferror(dict_f) != 0) {
            free(new_node);
            printf("Error reading dictionary file.\n");
            return false;
        }
        unsigned int hash_num = hash(new_node->word, TABLE_SIZE);
        dict->count += 1;

        if (dict->buckets[hash_num] == NULL) {
            new_node->next = NULL;
            dict->buckets[hash_num] = new_node;
        }
        else {
            new_node->next = dict->buckets[hash_num];
            dict->buckets[hash_num] = new_node;
        }
    }   
    
    return true;
}   

/* Size: Returns number of words in dictionary if loaded
 * else 0 if not yet loaded. */
unsigned int size(void) {
    if (dict == NULL) {
        return 0;
    }
    else {
        return dict->count;
    }
}

/* Unload: Frees memory malloc'd by load. Returns true if
 * memory is successfully returned to the manager. */
bool unload(void) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        clearList(&dict->buckets[i]);   
    }    
    free(dict);
    return true;
}

void clearList(node** head) {
    node* cursor, temp;
    cursor = *head;

    while(cursor) {
        temp = cursor;
        cursor = cursor->next;
        free(temp);
    }
    *head = NULL;
}

/* Hash: Returns an int between 0 (sigfnifying a fault) and max - 1
 * to be used inserting data in an appropriate section of a 
 * hash table. (Modified version of SDBM hash in "General Purpose
 * Hash Function Algorithms" found on partow.net) */
unsigned int hash(char* string, int max) {
    unsigned int hash = 0;
    unsigned int i = 0;

    char c = string[i];
    while(c != '\n' && c != '\0') {
        hash = (*string) + (hash << 6) + (hash << 16) - hash;

        string++;
        i += 1;
        c = string[i];
    }

    hash = hash % max;
    return hash;
}

