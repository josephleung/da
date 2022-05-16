#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_CAPACITY 5
#define BUFF_TOKENSIZE 1

static unsigned char buff_space[BUFF_CAPACITY];

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
        printf("underflow during read\n");
        return -1;
    }

    memcpy(data, buffer->read_pointer, buffer->token_size);
    *(char *)buffer->read_pointer = 0;

    if (buffer->read_pointer == buffer->buffer_end)
    {
        buffer->read_pointer = buffer->buffer_start;
    }
    else
    {
        buffer->read_pointer += buffer->token_size;
    }
    buffer->population--;

    return 0;
}

int buffer_write(buffer_struct_t *buffer, void *data)
{
    if (buffer->population == buffer->capacity)
    {
        printf("overflow during write\n");
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

void print_buff_p(unsigned char *buffer_space)
{
    unsigned int data;
    for (int i = 0; i < BUFF_CAPACITY; i++)
    {
        data = *buffer_space;
        printf("*%d", data);
        buffer_space++;
    }
}

void print_buff(void)
{
    for (int i = 0; i < BUFF_CAPACITY; i++)
    {
        printf("-%d", buff_space[i]);
    }
    printf("\n");
}

int main()
{
    printf("current function: %s\n", __func__);
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
    for (i = 0; i <= BUFF_CAPACITY; i++)
    {
        if (!buffer_write(mybuffer_p, &a))
        {
            printf("\n%d.\n", a);
            print_buff_p(buff_space);
            // print_buff();
        }
        a++;
    }

    printf("\n");

    for (i = 0; i <= BUFF_CAPACITY; i++)
    {
        if (!buffer_read(mybuffer_p, &a))
        {
            printf("\n%d.\n", a);
            print_buff_p(buff_space);
            // print_buff();
        }
    }
#endif
}