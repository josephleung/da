#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 5

typedef struct buffer
{
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int size;
} buffer_t;

void init_buffer(buffer_t *buff)
{
    buff->head = 0;
    buff->tail = 0;
    buff->size = 0;
}

int is_full(buffer_t *buff)
{
    return buff->size == BUFFER_SIZE;
}

int is_empty(buffer_t *buff)
{
    return buff->size == 0;
}

int enqueue(buffer_t *buff, int *p_val)
{
    if(is_full(buff))
    {
        printf("Buffer is full\n");
        return -1;
    }

    buff->buffer[buff->tail] = *p_val;
    buff->tail = (buff->tail + 1) % BUFFER_SIZE;
    buff->size++;
    return 0;
}

int dequeue(buffer_t *buff, int *p_val)
{
    if(is_empty(buff))
    {
        printf("Buffer is empty\n");
        return -1;
    }

    *p_val = buff->buffer[buff->head];
    buff->head = (buff->head + 1) % BUFFER_SIZE;
    buff->size--;

    return 0;
}

int main()
{
    buffer_t buffer;
    buffer_t *p_buffer = &buffer;
    init_buffer(p_buffer);

    int temp;
    temp = 1;
    enqueue(p_buffer, &temp);
    temp = 2;
    enqueue(p_buffer, &temp);
    temp = 3;
    enqueue(p_buffer, &temp);

    dequeue(p_buffer, &temp);
    printf("Dequeued: %d\n", temp);
    dequeue(p_buffer, &temp);
    printf("Dequeued: %d\n", temp);


    while (!is_empty(p_buffer))
    {
        dequeue(p_buffer, &temp);
        printf("Dequeued: %d\n", temp);
    }

    return 0;
}