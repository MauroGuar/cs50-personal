// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

const unsigned int N = 143107;

// Hash table
node *table[N];

unsigned int loads = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word) {
    unsigned int hash_value = hash(word);
    for (node *i = table[hash_value]; i != NULL; i = i->next) {
        if (strcasecmp(i->word, word) == 0) {
            return true;
        }
    }
    return false;
}

unsigned int calculateChar(char character) {
    if (character == '\'') { return character; }
    return toupper(character) - 'A';
}

// Hashes word to a number
unsigned int hash(const char *word) {
    const short BASE = 31;
    unsigned int hash_value = 0;
    for (int i = 0; i < strlen(word); ++i) {
        hash_value = (hash_value * BASE) + calculateChar(word[i]);
        hash_value %= N;
    }
    return hash_value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL) {
        printf("Error opening dictionary file.");
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(dict_file, "%45s", word) != EOF) {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL) {
            printf("Memory allocation failed.\n");
            fclose(dict_file);
            return false;
        }
        strcpy(new_node->word, word);
        new_node->next = NULL;

        unsigned int hash_value = hash(word);
        if (table[hash_value] == NULL) {
            table[hash_value] = new_node;
        } else {
            node *current = table[hash_value];
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
        loads++;
    }
    fclose(dict_file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    return loads;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {
    for (int i = 0; i < N; ++i) {
        node *first_node = table[i];
        while (first_node != NULL) {
            node *temp = first_node;
            first_node = first_node->next;
            free(temp);
        }
    }
    return true;
}
