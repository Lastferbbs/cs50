#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define HASHTABLE_SIZE 65536
#define LENGTH 45
#define DICTIONARY "dictionaries/small"

typedef struct node
    {
        char word[LENGTH + 1];
        struct node *next;
    }node;

int hash_it(char* needs_hashing);
bool check(const char *word);
node *hashtable[HASHTABLE_SIZE] = {NULL};

int main (void)
{

    char *dictionary = DICTIONARY;
    FILE *file = fopen(dictionary, "r");
    char word[LENGTH + 1];
    char* checking = "brushfires"; //brushfire i public taki sam hash!!!

    while(fscanf(file, "%s", word) != EOF)
    {
        node* new_node = malloc(sizeof(node));
        if(new_node == NULL)
        {
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
            new_node->next = NULL;
        }



    }
printf("%s. \n", hashtable[43655]->word);
bool x = check(checking);
printf("%d\n", x);
return true;
}

bool check(const char *word)
{
    int size = strlen(word);
    char* check1 = malloc(size);
    memcpy(check1, word, size);

    printf("%s\n", check1);
    int hashing = hash_it(check1);

    node* current = hashtable[hashing];

    while(current != NULL)
    {
        if(strcmp(check1, current->word) == 0)
        {
        return true;
        }
        current = current->next;
    }
    return false;
}



int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}