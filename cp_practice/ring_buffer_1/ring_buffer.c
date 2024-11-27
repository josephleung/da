#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

typedef struct
{
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int size;
} RingBuffer;

void initBuffer(RingBuffer *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->size = 0;
}

int isFull(RingBuffer *rb)
{
    return rb->size == BUFFER_SIZE;
}

int isEmpty(RingBuffer *rb)
{
    return rb->size == 0;
}

void enqueue(RingBuffer *rb, int value)
{
    if (isFull(rb))
    {
        printf("Buffer is full\n");
        return;
    }
    rb->buffer[rb->tail] = value;
    rb->tail = (rb->tail + 1) % BUFFER_SIZE;
    rb->size++;
}

int dequeue(RingBuffer *rb)
{
    if (isEmpty(rb))
    {
        printf("Buffer is empty\n");
        return -1;
    }
    int value = rb->buffer[rb->head];
    rb->head = (rb->head + 1) % BUFFER_SIZE;
    rb->size--;
    return value;
}

int main()
{
    RingBuffer rb;
    initBuffer(&rb);

    enqueue(&rb, 1);
    enqueue(&rb, 2);
    enqueue(&rb, 3);
    enqueue(&rb, 4);
    enqueue(&rb, 5);

    printf("Dequeued: %d\n", dequeue(&rb));
    printf("Dequeued: %d\n", dequeue(&rb));

    enqueue(&rb, 6);
    enqueue(&rb, 7);

    while (!isEmpty(&rb))
    {
        printf("Dequeued: %d\n", dequeue(&rb));
    }

    return 0;
}