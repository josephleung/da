#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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

int main()
{
    char s[] = " the   sky is blue ";
    reverseWords(s);
    printf("Reversed words: \"%s\"\n", s); // Output: "blue is sky the"
    return 0;
}