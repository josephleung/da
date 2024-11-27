#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_CAPACITY 3
#define BUFF_TOKEN_SIZE 1

enum return_codes
{
    SUCCESS = 0,
    OVERFLOW = 1,
    UNDERFLOW = 2,
};

typedef struct buffer_struct
{
    int capacity;
    int population;
    void *buffer_start;
    void *buffer_end;
    void *buffer_op_ptr;
    int token_size;
} buffer_struct_t;

void buffer_reset(buffer_struct_t *buffer)
{
    buffer->population = 0;
    buffer->buffer_op_ptr = buffer->buffer_start;
}

buffer_struct_t *buffer_new(int capacity, int token_size, void *buffer_pointer, void *buffer_space)
{
    buffer_struct_t *buffer = buffer_pointer;
    buffer->capacity = capacity;
    buffer->token_size = token_size;
    buffer->buffer_start = buffer_space;
    buffer->buffer_end = buffer->buffer_start + capacity * token_size;
    buffer_reset(buffer);
    return buffer;
}

int buffer_write(buffer_struct_t *buffer, void *data)
{
    if(buffer->population == buffer->capacity)
    {
        printf("overflow\n");
        return OVERFLOW;
    }

    memcpy(buffer->buffer_op_ptr, data, buffer->token_size);

    if(buffer->buffer_op_ptr == buffer->buffer_end)
    {
        buffer->buffer_op_ptr = buffer->buffer_start;
    }
    else
    {
        buffer->buffer_op_ptr += buffer->token_size;
    }

    buffer->population++;

    return SUCCESS;
}

int buffer_read(buffer_struct_t *buffer, void *data)
{
    if(buffer->population == 0)
    {
        printf("underflow\n");
        return UNDERFLOW;
    }

    if(buffer->buffer_op_ptr == buffer->buffer_start)
    {
        buffer->buffer_op_ptr = buffer->buffer_end;
    }
    else
    {
        buffer->buffer_op_ptr -= buffer->token_size;
    }

    memcpy(data, buffer->buffer_op_ptr, buffer->token_size);

    buffer->population--;

    return SUCCESS;
}

static unsigned char buff_space[BUFF_CAPACITY];
int main()
{
    buffer_struct_t buffer;
    buffer_struct_t *p_buffer = &buffer;
    p_buffer = buffer_new(BUFF_CAPACITY, BUFF_TOKEN_SIZE, p_buffer, buff_space);

    int a;
    int i;
    for (i = 0, a = 1; i <= 3; i++)
    {
        if (!buffer_write(p_buffer, &a))
            printf("%d, ", a);
        a++;
    }

    printf("\n");

    for (i = 0; i <= 3; i++)
    {
        if (!buffer_read(p_buffer, &a))
            printf("%d, ", a);
    }
}