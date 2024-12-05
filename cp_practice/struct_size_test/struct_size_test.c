#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct free_block
{
    char index;
    char marker_0;
    int a;
    int *b;
    char *data;
    char marker_1;
    // struct free_block *next;
    // char marker_2;
} free_block_t;

int main()
{
    int a = 3;
    int *p_a = &a;

    printf("a:%d, p_a:%x\n", a, p_a);
    printf("&a:%x, *p_a:%d\n", &a, *p_a);

    printf("sizeof(free_block_t):%d\n", (int)sizeof(free_block_t));

    return 0;
}