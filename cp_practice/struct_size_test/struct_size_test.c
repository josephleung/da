#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


// https://stackoverflow.com/questions/3318410/pragma-pack-effect
// #pragma pack(1)
typedef struct free_block
{
    char index;
    // char marker_0;
    // int a;
    // int *b;
    // char *data;
    // char marker_1;
    struct free_block *next;
    // char marker_2;
} free_block_t;
// #pragma pack()

typedef struct
{
    uint16_t count;
    uint16_t data[2];
    uint32_t timestamp;
} packet_S;

int main()
{
    int a = 3;
    int *p_a = &a;

    printf("a:%d, p_a:%x\n", a, (unsigned int)p_a);
    printf("&a:%x, *p_a:%d\n", (unsigned int)&a, *p_a);

    printf("sizeof(free_block_t):%d\n", (int)sizeof(free_block_t));


    printf("sizeof(packet_S):%d\n", (int)sizeof(packet_S));

    unsigned int x = 0xaabbccdd;
    char *c = (char*)&x;
    if (*c)
    {
        printf("*c: %x, Machine is Little Endian\n", *c);
    }
    else
    {
        printf("Machine is Big Endian\n");
    }
    return 0;
}