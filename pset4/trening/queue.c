#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 100

typedef struct _queue
{
    int array[CAPACITY];
    int front;
    int size;
} queue;

void enqueue(queue* q, int data);
int dequeue(queue* q);

int main(void)
{
    queue q;
    q.front = 0;
    q.size = 0;
    enqueue(&q, 10);
    enqueue(&q, 12);
    int x = dequeue(&q);
    enqueue(&q, 25);
    printf("%i,\n%i\n%i\n", q.array[1], x, q.array[2]);
}


void enqueue(queue* q, int data)
{
    q->array[q->front + q->size] = data;
    q->size++;
}


int dequeue(queue* q)
{
    int retval = q->array[q->front];
    q->front++;
    q->size--;
    return retval;
}