#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int gcd(int a, int b)
{
    while (b)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

char *gcdOfStrings(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // Check if str1 + str2 is equal to str2 + str1
    char combined1[len1 + len2 + 1];
    char combined2[len1 + len2 + 1];
    strcpy(combined1, str1);
    strcat(combined1, str2);
    strcpy(combined2, str2);
    strcat(combined2, str1);

    if (strcmp(combined1, combined2) != 0)
    {
        return "";
    }

    int gcd_length = gcd(len1, len2);
    char *result = (char *)malloc((gcd_length + 1) * sizeof(char));
    strncpy(result, str1, gcd_length);
    result[gcd_length] = '\0';

    return result;
}

int main()
{
    char str1[] = "ABCABC";
    char str2[] = "ABC";
    printf("%s\n", gcdOfStrings(str1, str2)); // Output: "ABC"
    return 0;
}