#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#if 0
// Function to reverse a portion of the string
void reverse(char *begin, char *end)
{
    char temp;
    while (begin < end)
    {
        temp = *begin;
        *begin++ = *end;
        *end-- = temp;
    }
}

#if 0
// Function to reverse words in the string
char *reverseWords(char *s)
{
    // Remove leading and trailing spaces
    while (*s == ' ')
    {
        s++;
    }
    int len = strlen(s);
    while (len > 0 && s[len - 1] == ' ')
    {
        s[--len] = '\0';
    }

    // Reverse individual words
    char *word_begin = s;
    char *temp = s;
    while (*temp)
    {
        temp++;
        if (*temp == ' ' || *temp == '\0')
        {
            reverse(word_begin, temp - 1);
            // It ensures that we correctly update the starting position for the next word after reversing the current word.
            word_begin = temp + 1;
        }
    }

    // Reverse the entire string
    reverse(s, temp - 1);

    // Remove extra spaces between words
    char *dest = s;
    temp = s;
    while (*temp)
    {
        if (*temp != ' ' || (*(temp + 1) != ' ' && *(temp + 1) != '\0'))
        {
            *dest++ = *temp;
        }
        temp++;
    }
    *dest = '\0';

    return s;
}

#else
// Function to trim leading and trailing spaces
void trimSpaces(char *str, char **start, char **end)
{
    *start = str;
    while (**start == ' ')
        (*start)++;
    *end = str + strlen(str) - 1;
    while (**end == ' ')
        (*end)--;
    *end = *end + 1;
}

// Function to reverse the words in a string
void reverseWords(char *s)
{
    char *start;
    char *end;
    trimSpaces(s, &start, &end);

    if (start >= end)
    {
        // The string has only spaces
        s[0] = '\0';
        return;
    }

    // Reverse the entire string
    reverse(start, end - 1);

    // Reverse each word in the string
    char *wordStart = start;
    char *wordEnd;
    while (wordStart < end)
    {
        // Find the end of the word
        wordEnd = wordStart;
        while (wordEnd < end && *wordEnd != ' ')
            wordEnd++;

        // Reverse the word
        reverse(wordStart, wordEnd - 1);

        // Move to the next word
        wordStart = wordEnd;
        while (wordStart < end && *wordStart == ' ')
            wordStart++;
    }

    // Remove extra spaces between words
    char *dst = s;
    while (start < end)
    {
        printf("start dst: \"%s\", \t s: \"%s\" \t \t", dst, s);
        if (*start != ' ' || (*(start - 1) != ' '))
        {
            *dst++ = *start;
        }
        start++;
        printf("end dst: \"%s\", \t\t s: \"%s\"\n\n", dst, s);
    }
    *dst = '\0';
}
#endif
#else
void reverse(char *begin, char *end)
{
    char temp;
    while (begin < end)
    {
        temp = *begin;
        *begin++ = *end;
        *end-- = temp;
    }
}

char *reverseWords(char *s)
{
    char *start = s;
    char *end = s + strlen(s) - 1;

    // Remove leading and trailing spaces
    while (*start == ' ')
    {
        start++;
    }
    while (end > start && *end == ' ')
    {
        end--;
    }
    end++;

    // Reverse the entire string
    char *p = start;
    while (p < end)
    {
        p++;
    }
    reverse(start, p - 1);

    // Reverse each word in the string
    char *word_begin = NULL;
    char *word_end = NULL;
    p = start;
    while (p < end)
    {
        if (word_begin == NULL && *p != ' ')
        {
            word_begin = p;
        }
        if (word_begin != NULL && (*(p + 1) == ' ' || *(p + 1) == '\0'))
        {
            word_end = p;
            reverse(word_begin, word_end);
            word_begin = NULL;
        }
        p++;
    }

    // Remove extra spaces between words
    char *dest = start;
    p = start;
    while (p < end)
    {
        if (*p != ' ' || (*(p + 1) != ' ' && *(p + 1) != '\0'))
        {
            *dest++ = *p;
        }
        p++;
    }
    *dest = '\0';

    return start;
}
#endif

int main()
{
    char s[] = " the   sky is blue ";
    reverseWords(s);
    printf("Reversed words: \"%s\"\n", s); // Output: "blue is sky the"
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 4) Memory dump
//    The following memory dump was taken while debugging an issue.
//
// Memory Dump:
// Address:  Byte:

// 0x1010    0x6F
// 0x1011    0xD5
// 0x1012    0x70
// 0x1013    0x9E
// 0x1014    0x94
// 0x1015    0x99
// 0x1016    0x4A
// 0x1017    0xBA
// 0x1018    0xCA
// 0x1019    0xB2
// 0x101A    0x32
// 0x101B    0xE6
// 0x101C    0x8E
// 0x101D    0xB9
// 0x101E    0xC5
// 0x101F    0x2E
// 0x1020    0xC3
//
// System is 32-bit, little-endian.
// A variable called myPacket is of type packet_S (typedef below).
// (Default compiler options; unpacked, naturally aligned.)
// The address of myPacket is 0x1010.
//
typedef struct
{
    uint8_t count;
    uint16_t data[2];
    uint32_t timestamp;
} packet_S;
 
// a) What are the values of each member of myPacket?
// count = 
// data[0] = 
// timestamp = 