// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"


#define HASHTABLE_SIZE 65537
#define DICTIONARY "dictionaries/large"


typedef struct node
    {
        char word[LENGTH + 1];
        struct node *next;
    }node;

unsigned int hash_it(char* needs_hashing);
node *hashtable[HASHTABLE_SIZE] = {NULL};

unsigned int rozmiar = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char check[strlen(word)+1];
    strcpy(check, word);

    for(int i = 0; check[i]; i++)
    {
        check[i] = tolower(check[i]);
    }
    int hashing = hash_it(check);

    node* current = hashtable[hashing];

    while(current != NULL)
    {
        if(strcmp(check, current->word) == 0)
        {
        return true;
        }
        current = current->next;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    char word[LENGTH + 1];

    while(fscanf(file, "%s", word) != EOF)
    {
        rozmiar++;
        node* new_node = malloc(sizeof(node));
        if(new_node == NULL)
        {
            printf("%i.\n", rozmiar);
            unload();
            return false;
        }
        strcpy(new_node->word, word);
        int hashing = hash_it(word);

        if(hashtable[hashing] != NULL)
        {
            new_node->next = hashtable[hashing];
            hashtable[hashing] = new_node;
        }

        if(hashtable[hashing] == NULL)
        {
            hashtable[hashing] = new_node;
            new_node->next=NULL;
        }




    }

    fclose(file);
    return true;



}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if(rozmiar > 0)
    return (unsigned int) rozmiar;

    else
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node* trav = NULL;
    for(int i = 1; i < HASHTABLE_SIZE; i++)
    {
        trav = hashtable[i];
        while (trav != NULL)
        {
            node* temp = trav;
            trav = trav->next;
            free(temp);
        }
    }
    return true;
}


unsigned int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}


/*char word[LENGTH + 1];
    node *hashtable[HASHTABLE_SIZE];

    FILE *file = fopen(dictionary, "r");


    while(fscanf(file, "%s", word) != EOF)
    {
        word = hash_it(word)

    }

    return false;*/