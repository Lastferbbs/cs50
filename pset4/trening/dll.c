#include <stdio.h>
#include <stdlib.h>




typedef struct dllist
{
    double val;
    struct dllist* next;
    struct dllist* prev;
}
dllnode;

void push(dllnode** head, double val);
int pop(dllnode** head);
int remove_last(dllnode* head);
int remove_by_index(dllnode ** head, int n);
int remove_by_value(dllnode ** head, int n);



int main(void)
{
   dllnode* head = NULL;
   head = malloc(sizeof(dllnode));
   if(head == NULL)
   {
       return 1;
   }

   head->prev = NULL;
   head->val = 1;
   head->next = malloc(sizeof(dllnode));
   head->next->prev = head;
   head->next->val = 2;
   head->next->next = NULL;

    dllnode* current = head;

    push(&head, 2);
    push(&head, 3);
    push(&head, 9);
    push(&head, 9);
    remove_by_index(&head, 3);
    remove_by_value(&head, 1);

    int x = 0;

     current = head;
     while (current->next != NULL)
    {
        current = current->next;
        x++;
    }

    for(int i = 0; i <= x; i++)
    {
        printf("%f\n", current->val);
        current = current->prev;

    }


}


void push(dllnode** head, double val) //dodaje element na początku listy
{
    dllnode* new_node;
    new_node = malloc(sizeof(dllnode));

    new_node->val = val;
    new_node->next = *head;
    new_node->prev = NULL;
    (*head)->prev = new_node;
    *head = new_node;
}

int pop(dllnode** head) {
    int retval = -1;
    dllnode * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;
    (*head)->prev = NULL;

    return retval;
}

int remove_last(dllnode* head)
{
    dllnode* current = head;
    dllnode* store_prev = NULL;
    int retval = -1;

    while (current->next != NULL)
    {
        current = current->next;
    }

    store_prev = current->prev;
    store_prev->next = NULL;
    current->val = retval;
    free(current);
    return retval;

}


int remove_by_index(dllnode ** head, int n) {
    int i = 0;
    int retval = -1;
    dllnode* current = *head;
    //dllnode* temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (i = 0; i < n; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    //temp_node = current->next;

    current->next->prev = current->prev;
    current->prev->next = current->next;
    free(current);

    /*current->next = temp_node->next;
    current->next->prev = temp_node->prev;
    free(temp_node);*/

    return retval;

}


int remove_by_value(dllnode ** head, int v) {
    int retval = v;
    dllnode * current = *head;


    if (v == 0) {
        return pop(head);
    }


    while (current->val != v)
    {
        current = current->next;
        if(current->next == NULL)
        return -2;
    }

    current->next->prev = current->prev;
    current->prev->next = current->next;
    free(current);

    return retval;
}




