#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int compress(char *chars, int charsSize)
{
    if (charsSize <= 1)
        return charsSize;

    int writePos = 0;
    int count = 1;

    for (int i = 1; i <= charsSize; i++)
    {
        if (i < charsSize && chars[i] == chars[i - 1])
        {
            count++;
        }
        else
        {
            chars[writePos++] = chars[i - 1];
            if (count > 1)
            {
                char countStr[10];
                sprintf(countStr, "%d", count);
                for (int j = 0; countStr[j]; j++)
                {
                    chars[writePos++] = countStr[j];
                }
            }
            count = 1;
        }
    }

    return writePos;
}

int main()
{
    char chars[] = {'a', 'a', 'b', 'b', 'c', 'c', 'c'};
    int charsSize = sizeof(chars) / sizeof(chars[0]);
    int compressedSize = compress(chars, charsSize);
    printf("Compressed size: %d\n", compressedSize);
    for (int i = 0; i < compressedSize; i++)
    {
        printf("%c", chars[i]);
    }
    printf("\n");

    char chars_1[] = {'a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'};
    charsSize = sizeof(chars_1) / sizeof(chars_1[0]);
    compressedSize = compress(chars_1, charsSize);
    printf("Compressed size: %d\n", compressedSize);
    for (int i = 0; i < compressedSize; i++)
    {
        printf("%c", chars_1[i]);
    }
    printf("\n");
    return 0;
}