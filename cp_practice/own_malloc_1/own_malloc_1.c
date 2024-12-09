#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 128
#define BLOCK_PAYLOAD_SIZE 3

enum ret_status
{
    SUCCESS = 0,
    FAIL_NO_FREE_BLOCK = 1
};

unsigned char buffer[BUFFER_SIZE];

// #pragma pack(1)
typedef struct data_block
{
    unsigned int index;
    unsigned int marker_0;
    char *data;
    unsigned int marker_1;
    struct data_block *next;
    unsigned int marker_2;
    bool is_free;
    unsigned int marker_3;
} data_block_t;
// #pragma pack()

typedef struct block_manager
{
    data_block_t *head;
    data_block_t *tail;
    unsigned int total_blocks;
    unsigned int free_blocks;
} block_manager_t;

block_manager_t block_manager;

void block_init(void *buffer_location)
{
    int total_blocks = BUFFER_SIZE / (BLOCK_PAYLOAD_SIZE + sizeof(data_block_t));
    int i = 0;

    printf("+++%s\n", __func__);

    printf("BUFFER_SIZE:%d, sizeof(data_block_t):%d, Total blocks:%d, (BLOCK_PAYLOAD_SIZE + sizeof(data_block_t):%d\n",
           BUFFER_SIZE, (int)sizeof(data_block_t), total_blocks, (int)(BLOCK_PAYLOAD_SIZE + sizeof(data_block_t)));

    data_block_t *block = (data_block_t *)buffer_location;

    block_manager.head = (data_block_t *)buffer_location;
    block_manager.total_blocks = total_blocks;
    block_manager.free_blocks = total_blocks;

    for (i = 0; i < total_blocks; i++)
    {
        block->index = i;
        block->marker_0 = 0x0a0a0a0a;
        block->data = (void *)block + sizeof(data_block_t);
        block->marker_1 = 0x1a1a1a1a;
        block->next = (data_block_t *)((void *)block + BLOCK_PAYLOAD_SIZE + sizeof(data_block_t));
        block->marker_2 = 0x2a2a2a2a;
        block->is_free = true;
        block->marker_3 = 0x3a3a3a3a;

        printf("Block index: %d, Block location: %p, Block data location: %p, Block next location: %p\n", block->index, block, block->data, block->next);

        if (i == total_blocks - 1)
        {
            block->next = NULL;
            block_manager.tail = block;
        }
        else
        {
            block = block->next;
        }
    }

    printf("Block manager head: %p, Block manager tail: %p, Block manager total_blocks: %d\n", block_manager.head, block_manager.tail, block_manager.total_blocks);

    printf("+++End of %s\n", __func__);
}

void print_blocks(void)
{
    data_block_t *block = (data_block_t *)buffer;

    printf("+++%s\n", __func__);

    while (block != NULL)
    {
        printf("    Block index: %d, data:%x\n", block->index, *block->data);
        block = block->next;
    }
    printf("+++End of %s\n", __func__);
}

void put_to_tail(data_block_t *block)
{
    block_manager.tail->next = block;
    block_manager.tail = block;
    block_manager.tail->next = NULL;
}

unsigned int block_write(char *data)
{
    data_block_t *block = (data_block_t *)buffer;

    printf("+++%s\n", __func__);
    while (block != NULL)
    {
        if (block->is_free == true)
        {
            memcpy(block->data, data, BLOCK_PAYLOAD_SIZE);
            block->is_free = false;
            printf("     Block index: %d, write:0x%x\n", block->index, *block->data);
            
            printf("+++End of %s\n", __func__);
            return SUCCESS;
        }
        block = block->next;
    }

    printf("+++End of %s\n", __func__);
    return FAIL_NO_FREE_BLOCK;
}

void test_write_blocks(void)
{
    int i = 0;
    char data = 0;

    printf("+++%s\n", __func__);
    do 
    {
        data = i | 0x80;
        printf("\nBlock index: %d, write:0x%x\n", i, data);
        i++;
    }
    while (block_write(&data) == SUCCESS);

    printf("+++End of %s\n", __func__);
}

void dump_buffer()
{
    int i = 0;
    unsigned int block_size = BLOCK_PAYLOAD_SIZE + sizeof(data_block_t);

    printf("\n\n");
    printf("+++%s\n", __func__);
    for (i = 0; i < BUFFER_SIZE; i++)
    {
        printf("0x%02x ", buffer[i]);
        if ((i + 1) % block_size == 0)
        {
            printf("\n");
        }
    }
    printf("\n+++End of %s\n", __func__);
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
    printf("sizeof data_block_t: %d\n", (int)sizeof(data_block_t));

    return SUCCESS;
}