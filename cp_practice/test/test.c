#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 1024
#define NUM_BLOCKS 100

typedef struct Block {
    struct Block *next;
    char data[BLOCK_SIZE];
} Block;

typedef struct BlockAllocator {
    Block *free_list;
    Block blocks[NUM_BLOCKS];
} BlockAllocator;

void init_allocator(BlockAllocator *allocator) {
    allocator->free_list = NULL;
    for (int i = 0; i < NUM_BLOCKS; i++) {
        allocator->blocks[i].next = allocator->free_list;
        allocator->free_list = &allocator->blocks[i];
    }
}

void *alloc(BlockAllocator *allocator) {
    if (allocator->free_list == NULL) {
        return NULL; // No free blocks available
    }
    Block *block = allocator->free_list;
    allocator->free_list = block->next;
    return block->data;
}

size_t my_offsetof(size_t member_offset) {
    return member_offset;
}

void free_block(BlockAllocator *allocator, void *ptr) {
    Block *block = (Block *)((char *)ptr - my_offsetof((size_t)&((Block *)0)->data));
    block->next = allocator->free_list;
    allocator->free_list = block;
}

int main() {
    BlockAllocator allocator;
    init_allocator(&allocator);

    void *block1 = alloc(&allocator);
    if (block1 != NULL) {
        printf("Block1 allocated\n");
    }

    void *block2 = alloc(&allocator);
    if (block2 != NULL) {
        printf("Block2 allocated\n");
    }

    free_block(&allocator, block1);
    printf("Block1 freed\n");

    void *block3 = alloc(&allocator);
    if (block3 != NULL) {
        printf("Block3 allocated\n");
    }

    return 0;
}