#include <stdio.h>
#include <stdlib.h>




typedef struct sllist
{
    double val;
    struct sllist* next;
}
sllnode;

void push(sllnode** head, double val);
int pop(sllnode ** head);
int remove_by_value(sllnode ** head, double v);
int remove_by_index(sllnode ** head, int n);



int main(void)
{
   sllnode* head = NULL;
   head = malloc(sizeof(sllnode));
   if(head == NULL)
   {
       return 1;
   }

   head->val = 1;
   head->next = malloc(sizeof(sllnode));
   head->next->val = 2;
   head->next->next = NULL;

   sllnode* current = head;

    while (current != NULL)
    {
        if(current->val == 2)
        {
            printf("%f\n", current->val); //wypisywanie szukanego elementu, można użyć do wyświetlenia całej listy
                                          //wystarczy usunąć "if"
        }
        current = current->next;
    }

    push(&head, 9);
    push(&head, 8);
    pop(&head);
    remove_by_value(&head, 12);
    remove_by_index(&head, 4);

    current = head;

     while (current != NULL)
    {
        printf("%f\n", current->val);
        current = current->next;
    }
}

void push(sllnode** head, double val) //dodaje element na początku listy
{
    sllnode* new_node;
    new_node = malloc(sizeof(sllnode));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

int pop(sllnode** head) {
    int retval = -1;
    sllnode* next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}




int remove_by_value(sllnode ** head, double v) {
    int retval = v;
    sllnode * current = *head;
    sllnode * temp_node = NULL;

    if (current->val == v) {
        return pop(head);
    }

    while (current->next->val != v)
    {
        current = current->next;
        if(current->next == NULL)
        return -2;
    }

    temp_node = current->next;
    current->next = temp_node->next;
    free(temp_node);

    return retval;

}

int remove_by_index(sllnode ** head, int n) {
    int i = 0;
    int retval = -1;
    sllnode * current = *head;
    sllnode * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    temp_node = current->next;
    if(temp_node == NULL)
    {
        return -1;
    }
    retval = temp_node->val;
    current->next = temp_node->next;
    free(temp_node);

    return retval;
}





