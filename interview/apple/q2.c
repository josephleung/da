#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*
* This is a circular buffer that allows enqueue or dequeue arbitrary
* amount of bytes. The buffer size is limited to BUF_SIZE.
*/

//ZL:this function name can be better (GetErrorString), plus we don't need to declear it static
//the original purpose can be achieved by making the string in this function static so we can access it in other functions
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
    //ZL: should use available space in buffer, not total buffer size. available space can be calculated by
    /**
    int usedSize = buf.write_index - buf.read_index;
    if (usedSize < 0)
    {
        usedSize += buf.size;
    }
    int availableSize =  buf.size - usedSize;
    */
    if (size > BUF_SIZE)
    {
        printf("%s", GetErrorString(3)); //ZL: could be better if we use the enum OVERFLOW instead of a number 3
        return 3;
    }

    //below section only condiders normal write_index > read_index condition, write_index < read_index (wrap around condition) is not considered, and this is the essence of a ring buffer...
    int part1 = buf.size - buf.write_index;               //if data size < (buf.size - buf.write_index), we should use data size as part1 size
    memcpy(client_buf, buf.buf + buf.write_index, part1); //1. src and dst reversed. 2. write_index not updated after data fill

    if (part1 != size)
    {
        int part2 = size - part1;
        memcpy(client_buf + part1, buf.buf[0], part2); //1. src and dst reversed. 2. write_index not updated
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
    if (size < BUF_SIZE) //ZL: same issue here, should use available space in buffer, not buff size
    {
        printf("%s", GetErrorString(2)); //ZL: could be better if we use the enum UNDERFLOW instead of a number 2
        return 2;
    }

    //ZL: same issue, wrap around situation (write_index < read_index) not considered
    int copy_size = buf.write_index - buf.read_index + 1;     //do not need +1, if we handle index properly. personally I'll point write index to the next available position and read index to current read position
    memcpy(client_buf, buf.buf + buf.write_index, copy_size); //1. buf.read_index should be used insteaed of buf.write_index. 2. read_index update needed

    return 0;
}

//already done with this function name / static type previously
static char *GetErrorString(int x)
{
    char errorString[20]; //ZL: declear it as a static variable so it won't get freed upon exiting this function: static char errorString[20];
                          //or we can declear this outside the function as a global variable which is prefered personally
    switch (x)
    {
    case 0:
        //ZL: we cannot do this to a array, use strcpy instead: strcpy(errorString, "Success -- No error.");
        errorString = "Success -- No error.";
        break;
    //ZL: also, we have underflow missing, case number also mismatch. 2:Underflow, 3:Overflow
    case 2:
        //ZL: we cannot do this to a array, use strcpy instead: strcpy(errorString, "Overflow!");
        errorString = "Overflow!";
        break;
    }
    //ZL: default missing, better to have a default to catch surprise, if there's any
    /*
    default:
        strcpy(errorString, "Unknown error!");
        break;
    */

    errorString[19] = 0; //ZL: this is not needed if we use strcpy
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
