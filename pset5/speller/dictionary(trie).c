#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"
#define DICTIONARY "dictionaries/large"

#define LENGTH 45


typedef struct node
    {
        bool is_word;
        struct node *children[27];
    }node;

bool check(const char *word);
bool unload(void);
void unload_helper(node* current);

node* root;

int rozmiar = 0;
int index = -1;

bool load(const char *dictionary)
{
    root = calloc(1, sizeof(node));
    FILE *file = fopen(dictionary, "r");
    char word[LENGTH + 1];

    while(fscanf(file, "%s", word) != EOF)
    {
        rozmiar++;
        node* current = root;
        for(int i = 0; word[i]; i++)
        {
            char child = word[i];
            if(isalpha(child))
            {
                index = child - 'a';
            }
            else
            index = 26;

            /*if(current == NULL)
            {
                node* new_node = malloc(sizeof(node));
                if(new_node == NULL)
                {
                    return false;
                }
                current->children[index] = new_node;
                current = current->children[index];
            }*/
            if (current->children[index] == NULL)
            {
                node* new_node = calloc(1, sizeof(node));
                if(new_node == NULL)
                    {
                        unload();
                        return false;
                    }
            current->children[index] = new_node;
            }

            current = current->children[index];
        }
        current->is_word = true;
    }
fclose(file);
return true;
}


bool check(const char *word)
{
    node* current = root;
    //strcpy(check, word);

    for(int i = 0; word[i]; i++)
    {

        char child = tolower(word[i]);
            if(isalpha(child))
            {
                index = child - 'a';
            }
            else
            index = 26;

        if (current->children[index] == NULL)
        return false;

        current = current->children[index];
    }

if(current->is_word == true)
return true;

return false;

}

unsigned int size(void)
{
    if(rozmiar > 0)
    return (unsigned int) rozmiar;

    else
    return 0;
}


bool unload(void)
{
    node* current = root;
    unload_helper(current);
    return true;
}


void unload_helper(node* current)
{
    for(int i = 0; i < 27; i++)
    {
        if(current->children[i] != NULL)
        {
            unload_helper(current->children[i]);
        }
    }

    free(current);

}