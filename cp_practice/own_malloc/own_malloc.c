#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 128
#define BLOCK_PAYLOAD_SIZE 16

unsigned int buffer[BUFFER_SIZE];

typedef struct free_block
{
    unsigned int index;
    char *data;
    struct free_block *next;
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
        block->data = (char *)block + sizeof(free_block_t);
        block->next = (free_block_t *)((char *)block + BLOCK_PAYLOAD_SIZE + sizeof(free_block_t));

        printf("Block index: %d, Block location: %p, Block data: %p, Block next: %p\n", block->index, block, block->data, block->next);

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
    while (block != NULL)
    {
        printf("Block index: %d, data:%s\n", block->index, block->data);
        block = block->next;
    }
}

void test_write_blocks(void)
{
    free_block_t *block = (free_block_t *)buffer;
    int i = 0;

    printf("\n  start test_write_blocks\n"); 
    while (block != NULL)
    {
        printf("     Block index: %d, write:%d\n", block->index, i);
        block->data = i;
        block = block->next;
        i++;
    }

    printf("  end test_write_blocks\n"); 
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

    return 0;
}