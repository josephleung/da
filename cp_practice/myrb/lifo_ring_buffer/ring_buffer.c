#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_CAPACITY 3
#define BUFF_TOKENSIZE 1

typedef struct buffer_struct
{
    int capacity;
    void *buffer_start;
    void *buffer_end;
    int population;
    void *read_pointer;
    void *write_pointer;
    int token_size;
} buffer_struct_t;

void buffer_reset(buffer_struct_t *buffer)
{
    buffer->write_pointer = buffer->buffer_start;
    buffer->read_pointer = buffer->buffer_start;
    buffer->population = 0;
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

int buffer_read(buffer_struct_t *buffer, void *data)
{
    if (buffer->population == 0)
    {
        printf("underflow\n");
        return -1;
    }

    if (buffer->write_pointer == buffer->buffer_start)
    {
        buffer->write_pointer = buffer->buffer_end;
    }
    else
    {
        buffer->write_pointer = buffer->write_pointer - buffer->token_size;
    }
    memcpy(data, buffer->write_pointer, buffer->token_size);
    buffer->population--;

    return 0;
}

int buffer_write(buffer_struct_t *buffer, void *data)
{
    if (buffer->population == buffer->capacity)
    {
        printf("overflow\n");
        return -1;
    }
    memcpy(buffer->write_pointer, data, buffer->token_size);

    if (buffer->write_pointer == buffer->buffer_end)
    {
        buffer->write_pointer = buffer->buffer_start;
    }
    else
    {
        buffer->write_pointer += buffer->token_size;
    }

    buffer->population++;

    return 0;
}

static unsigned char buff_space[BUFF_CAPACITY];
int main()
{
    buffer_struct_t mybuffer;
    buffer_struct_t *mybuffer_p = &mybuffer;
    mybuffer_p = buffer_new(BUFF_CAPACITY, BUFF_TOKENSIZE, mybuffer_p, buff_space);

#if 0
    int a = 1;
    int i = 0;

    buffer_write(mybuffer, &a);
    printf("%dth: %d, ", i, a);

    printf("\n");

    buffer_read(mybuffer, &a);
    printf("%dth: %d, ", i, a);
#else
    int a = 1;
    int i;
    for (i = 0; i <= 3; i++)
    {
        if (!buffer_write(mybuffer_p, &a))
            printf("%d, ", a);
        a++;
    }

    printf("\n");

    for (i = 0; i <= 3; i++)
    {
        if (!buffer_read(mybuffer_p, &a))
            printf("%d, ", a);
    }
#endif
}