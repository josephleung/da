#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 128
#define BLOCK_PAYLOAD_SIZE 1

unsigned char buffer[BUFFER_SIZE];

typedef struct free_block
{
    unsigned int index;
    unsigned int marker_0;
    char *data;
    unsigned int marker_1;
    struct free_block *next;
    unsigned int marker_2;
} free_block_t;

void block_init(void *buffer_location)
{
    int total_blocks = BUFFER_SIZE / (BLOCK_PAYLOAD_SIZE + sizeof(free_block_t));
    int i = 0;

    printf("BUFFER_SIZE:%d, sizeof(free_block_t):%d, Total blocks:%d, (BLOCK_PAYLOAD_SIZE + sizeof(free_block_t):%d\n",
           BUFFER_SIZE, (int)sizeof(free_block_t), total_blocks, (int)(BLOCK_PAYLOAD_SIZE + sizeof(free_block_t)));

    free_block_t *block = (free_block_t *)buffer_location;

    for (i = 0; i < total_blocks; i++)
    {
        block->index = i;
        block->marker_0 = 0x11111111;
        block->data = (char *)block + sizeof(free_block_t);
        block->marker_1 = 0x22222222;
        block->next = (free_block_t *)((char *)block + BLOCK_PAYLOAD_SIZE + sizeof(free_block_t));
        block->marker_2 = 0x33333333;

        printf("Block index: %d, Block location: %p, Block data location: %p, Block next location: %p\n", block->index, block, block->data, block->next);

        if (i == total_blocks - 1)
        {
            block->next = NULL;
        }
        else
        {
            block = block->next;
        }
    }
}

void print_blocks(void)
{
    free_block_t *block = (free_block_t *)buffer;

    printf("\n  start print_blocks\n"); 
    while (block != NULL)
    {
        printf("Block index: %d, data:%x\n", block->index, *block->data);
        block = block->next;
    }
    printf("\n  end print_blocks\n"); 
}

void test_write_blocks(void)
{
    free_block_t *block = (free_block_t *)buffer;
    int i = 0;

    printf("\n  start test_write_blocks\n"); 
    while (block != NULL)
    {
        printf("     Block index: %d, write:%d\n", block->index, i);
        *block->data = i;
        block = block->next;
        i++;
    }

    printf("  end test_write_blocks\n"); 
}

void dump_buffer()
{
    int i = 0;
    unsigned int block_size = BLOCK_PAYLOAD_SIZE + sizeof(free_block_t);

    printf("\n\n");
    for (i = 0; i < BUFFER_SIZE; i++)
    {
        printf("0x%02x ", buffer[i]);
        if ((i + 1) % block_size == 0)
        {
            printf("\n");
        }

    }
    printf("\n\n");
}


// void *own_malloc(void)
// {

// }

// void own_free(void *ptr)
// {

// }

int main()
{
    block_init(buffer);
    print_blocks();
    test_write_blocks();
    print_blocks();

    dump_buffer();

    printf("sizeof buffer: %d\n", (int)sizeof(buffer));

    return 0;
}