#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 3

enum ret_val
{
    SUCCESS,
    ERR_OVERFLOW,
    ERR_UNDERFLOW,
    ERR_INVALID_PARAM
};

typedef struct buffer
{
    int head;
    int tail;
    int size;
    int *buf;
} buffer_t;

int init_buffer(buffer_t *buff, int clear_buffer)
{
    if(buff == NULL)
    {
        printf("Invalid buffer\n");
        return ERR_INVALID_PARAM;
    }

    if(clear_buffer == 1)
    {
        memset(buff->buf, 0, BUFFER_SIZE * sizeof(int));
    }

    buff->head = 0;
    buff->tail = 0;
    buff->size = 0;

    return SUCCESS;
}

int is_full(buffer_t *buff)
{
    if(buff == NULL)
    {
        printf("Invalid buffer\n");
        return ERR_INVALID_PARAM;
    }

    return buff->size == BUFFER_SIZE;
}

int is_empty(buffer_t *buff)
{
    if(buff == NULL)
    {
        printf("Invalid buffer\n");
        return ERR_INVALID_PARAM;
    }

    return buff->size == 0;
}

int enqueue(buffer_t *buff, int *p_val)
{
    if(buff == NULL)
    {
        printf("Invalid buffer\n");
        return ERR_INVALID_PARAM;
    }
    if(p_val == NULL)
    {
        printf("Invalid value\n");
        return ERR_INVALID_PARAM;
    }

    if(is_full(buff))
    {
        printf("Buffer is full\n");
        return ERR_OVERFLOW;
    }

    buff->buf[buff->tail] = *p_val;
    buff->tail = (buff->tail + 1) % BUFFER_SIZE;
    buff->size++;
    
    return SUCCESS;
}

int dequeue(buffer_t *buff, int *p_val)
{
    if(buff == NULL)
    {
        printf("Invalid buffer\n");
        return ERR_INVALID_PARAM;
    }

    if(p_val == NULL)
    {
        printf("Invalid value\n");
        return ERR_INVALID_PARAM;
    }

    if(is_empty(buff))
    {
        printf("Buffer is empty\n");
        return ERR_UNDERFLOW;
    }

    *p_val = buff->buf[buff->head];
    buff->head = (buff->head + 1) % BUFFER_SIZE;
    buff->size--;

    return SUCCESS;
}

int main()
{
    int buffer_array[BUFFER_SIZE];
    buffer_t buffer;
    buffer_t *p_buffer = &buffer;
    p_buffer->buf = buffer_array;
    init_buffer(p_buffer, 0);

    int temp;
    temp = 1;
    if(enqueue(p_buffer, &temp) == SUCCESS)
        printf("Enqueued: %d\n", temp);
    temp = 2;
    if(enqueue(p_buffer, &temp) == SUCCESS)
        printf("Enqueued: %d\n", temp);
    temp = 3;
    if(enqueue(p_buffer, &temp) == SUCCESS)
        printf("Enqueued: %d\n", temp);
    temp = 4;
    if(enqueue(p_buffer, &temp) == SUCCESS)
        printf("Enqueued: %d\n", temp);

    if(dequeue(p_buffer, &temp) == SUCCESS)
        printf("Dequeued: %d\n", temp);
    if(dequeue(p_buffer, &temp) == SUCCESS)
        printf("Dequeued: %d\n", temp);
    if(dequeue(p_buffer, &temp) == SUCCESS)
        printf("Dequeued: %d\n", temp);
    if(dequeue(p_buffer, &temp) == SUCCESS)
        printf("Dequeued: %d\n", temp);

    printf("buff0: %d\n", p_buffer->buf[0]);
    init_buffer(p_buffer, 1);
    printf("buff0: %d\n", p_buffer->buf[0]);

    return 0;
}