#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 5

enum ret_val
{
    SUCCESS,
    ERR_OVERFLOW,
    ERR_UNDERFLOW
};

typedef struct buffer
{
    int buffer[BUFFER_SIZE];
    int head;
    int tail;
    int size;
} buffer_t;

void init_buffer(buffer_t *buff, int clear_buffer)
{
    if(clear_buffer)
    {
        memset(buff->buffer, 0, sizeof(buff->buffer));
    }

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
        return ERR_OVERFLOW;
    }

    buff->buffer[buff->tail] = *p_val;
    buff->tail = (buff->tail + 1) % BUFFER_SIZE;
    buff->size++;
    return SUCCESS;
}

int dequeue(buffer_t *buff, int *p_val)
{
    if(is_empty(buff))
    {
        printf("Buffer is empty\n");
        return ERR_UNDERFLOW;
    }

    *p_val = buff->buffer[buff->head];
    buff->head = (buff->head + 1) % BUFFER_SIZE;
    buff->size--;

    return SUCCESS;
}

int main()
{
    buffer_t buffer;
    buffer_t *p_buffer = &buffer;
    init_buffer(p_buffer, 0);

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