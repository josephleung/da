#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to find the GCD of two numbers
#if 1
int gcd(int a, int b)
{
    // Find Minimum of a and b
    int result = ((a < b) ? a : b);
    while (result > 0)
    {
        // Check if both a and b are divisible by result
        if (a % result == 0 && b % result == 0)
        {
            break;
        }
        result--;
    }
    // return gcd of a nd b
    return result;
}
#else
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
#endif

// Function to compare two strings up to n characters
int my_strncmp(const char *s1, const char *s2, size_t n)
{
    while (n && *s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
        n--;
    }
    if (n == 0)
    {
        return 0;
    }
    else
    {
        return (*(unsigned char *)s1 - *(unsigned char *)s2);
    }
}

// Helper function to check if str can be formed by repeating sub
int canForm(char *str, char *sub)
{
    int lenStr = strlen(str);
    int lenSub = strlen(sub);
    printf("Function: %s\n", __func__);
    printf("str: %s, sub: %s\n", str, sub);

    for (int i = 0; i < lenStr; i += lenSub)
    {
        printf("canForm, i = %d\n", i);
        if (my_strncmp(str + i, sub, lenSub) != 0)
        {
            return 0;
        }
    }
    return 1;
}

// Function to find the GCD string
char *gcdOfStrings(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int gcdLen = gcd(len1, len2);

    printf("gcdLen %d\n", gcdLen);

    // Create a candidate GCD string from str1
    char *candidate = (char *)malloc((gcdLen + 1) * sizeof(char));
    strncpy(candidate, str1, gcdLen);
    candidate[gcdLen] = '\0';
    printf("candidate %s\n", candidate);

    // Check if candidate can form both str1 and str2
    if (canForm(str1, candidate) && canForm(str2, candidate))
    {
        return candidate;
    }
    else
    {
        free(candidate);
        return "";
    }
}

int main()
{
    char str1[] = "ABCABCABC";
    char str2[] = "ABCABC";

    char *result = gcdOfStrings(str1, str2);
    printf("GCD of strings: %s\n", result);

    // If memory was allocated for result, it should be freed. In this example, it's fine to let it be because result points to a string literal when there's no common divisor.
    return 0;
}
