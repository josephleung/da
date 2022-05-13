#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct buffer_struct
{
    int capacity;
    void* buffer_start;
    void* buffer_end;
    int population;
    void *read_pointer;
    void *write_pointer;
    int token_size;
} buffer_struct_t;

void buffer_reset(buffer_struct_t* buffer)
{
    buffer->write_pointer = buffer->buffer_start;
    buffer->read_pointer = buffer->buffer_start;
    buffer->population = 0;
}

buffer_struct_t* buffer_new(int capacity, int token_size, void* buffer_pointer)
{
    buffer_struct_t* buffer = buffer_pointer;
    buffer->capacity = capacity;
    buffer->token_size = token_size;
    buffer->buffer_start = buffer_pointer + sizeof(buffer_struct_t);
    buffer->buffer_end = buffer->buffer_start + (capacity - 1) * token_size;
    buffer_reset(buffer);
    return buffer;
}

int buffer_read(buffer_struct_t* buffer, void *data)
{
    if(buffer->population == 0)
    {
        return -1;
    }

    if(buffer->write_pointer == buffer->buffer_start)
    {
        buffer->write_pointer = buffer->buffer_end;
    }
    else
    {
        buffer->write_pointer = buffer
    }
}