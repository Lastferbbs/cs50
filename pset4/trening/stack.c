#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 100

typedef struct _stack
{
    int array[CAPACITY];
    int top;
}
stack;

void push(stack* s, int data);
int pop(stack* s);

int main(void)
{
    stack s;
    s.top = 0;
    push(&s, 11);
    push(&s, 13);
    push(&s, 15);
    push(&s, 17);
    pop(&s);

    printf("%i\n", s.array[2]);

}


void push(stack* s, int data)
{
    s->array[s->top] = data;
    s->top++;
}

int pop(stack* s)
{
    int retval = -1;
    s->top--;
    retval = s->array[s->top];
    printf("%d\n", retval);
    return retval;
}