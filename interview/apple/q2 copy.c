#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*
* This is a circular buffer that allows enqueue or dequeue arbitrary
* amount of bytes. The buffer size is limited to BUF_SIZE.
*/

//ZL:this function name can be better (getErrorString), plus we don't need to declear it static
//the original purpose is make the string static so we can access it in other functions
static char *GetErrorString(int x);

//ZL: can use enum for more human-readable error code, for example 
/**
 * enum ErrorCode
{
    SUCCESS = 0,
    UNDERFLOW = 2,
    OVERFLOW = 3,
};
 */

#define BUF_SIZE 4096

typedef struct
{
    int write_index;
    int read_index;
    char *buf;
    int size;
} circular_buf_t;

circular_buf_t buf;

/*
* Enqueue (size) bytes from (client_buf) to the local buf
* memory of (client_buf) is allocated by the caller
*/
int enqueue(char *client_buf, int size)
{
    //if (size > BUF_SIZE)  //ZL: should use available space in buffer, not buffer size
    int usedSize = buf.write_index - buf.read_index;
    if (usedSize < 0)
    {
        usedSize += buf.size;
    }
    if (size > buf.size - usedSize)
    {
        printf("%s", getErrorString(3));
        return 3;
    }

    int part1 = buf.size - buf.write_index;               //if write_index < read_index, we should use read_index - write_index
    memcpy(client_buf, buf.buf + buf.write_index, part1); //src and dst reversed. if part1 > size, we should use size. write_index not updated

    if (part1 != size) //part1 < size
    {
        int part2 = size - part1;
        memcpy(client_buf + part1, buf.buf[0], part2); //src and dst reversed. if part1 > size, we should use size. write_index not updated
    }

    return 0;
}

/*
* Dequeue (size) bytes from the local buf to (client_buf),
* (client_buf) is allocated by the caller. It is okay to assume
* (client_buf) is big enough to hold all the (size) bytes
*/
int dequeue(char *client_buf, int size)
{
    //if (size < BUF_SIZE)  //ZL: should use data in buffer, not buff size
    int usedSize = buf.write_index - buf.read_index;
    if (usedSize < 0)
    {
        usedSize += buf.size;
    }
    {
        printf("%s", getErrorString(2));
        return 2;
    }

    int copy_size = buf.write_index - buf.read_index + 1;  //do not need +1
    memcpy(client_buf, buf.buf + buf.write_index, copy_size);  //buf.read_index should be used

    //ZL: write_index < read_index


    return 0;
}

//static char *getErrorString(int x)
char *getErrorString(int x)
{
    //ZL: declear it as a static variable so it won't get freed upon exiting this function
    //char errorString[20];
    static char errorString[20];

    switch (x)
    {
    case 0:
        //ZL: we cannot do this to a array, use strcpy instead
        //errorString = "Success -- No error.";
        strcpy(errorString, "Success -- No error.");
        break;
    //ZL: also, we have underflow missing, case number also mismatch
    case 2:
        //errorString = "Overflow!";
        strcpy(errorString, "Overflow!");
        break;
    //ZL: default
    default:
        strcpy(errorString, "Unknown error!");
        break;
    }

    //ZL: not needed if we use strcpy
    //errorString[19] = 0;
    return errorString;
}

int main(int argc, char *argv[])
{
    // initialize buffer
    buf.buf = malloc(BUF_SIZE);
    buf.size = BUF_SIZE;

    // Perform enqueue() and dequeue();

    // All completed, return
    return 0;
}
