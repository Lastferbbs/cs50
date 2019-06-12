// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"
#include "speller.c"


#define HASHTABLE_SIZE 65536
#define DICTIONARY "dictionaries/large"


typedef struct node
    {
        char word[LENGTH + 1];
        struct node *next;
    }node;

int hash_it(char* needs_hashing);
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
/*bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    char word[LENGTH + 1];

    while(fscanf(file, "%s", word) != EOF)
    {
        rozmiar++;
        node* new_node = malloc(sizeof(node));
        if(new_node == NULL)
        {
            unload();
            return false;
        }
        strcpy(new_node->word, word);
        int hashing = hash_it(word);

        if(hashtable[hashing]->next == NULL)
        {
            hashtable[hashing] = new_node;
            new_node->next=NULL;
        }

        if(hashtable[hashing]->next != NULL)
        {
            new_node->next = hashtable[hashing]->next;
            hashtable[hashing] = new_node;
        }


    }


    return true;



}
*/

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
    for(int i = 0; 65536; i++)
    {
        trav = hashtable[i];
        while (trav != NULL)
        {
            node* temp = trav;
            trav = trav->next;
            free(temp);
        }
    }
    free(hashtable);
    return true;
}


/*int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}
*/


/*char word[LENGTH + 1];
    node *hashtable[HASHTABLE_SIZE];

    FILE *file = fopen(dictionary, "r");


    while(fscanf(file, "%s", word) != EOF)
    {
        word = hash_it(word)

    }

    return false;*/