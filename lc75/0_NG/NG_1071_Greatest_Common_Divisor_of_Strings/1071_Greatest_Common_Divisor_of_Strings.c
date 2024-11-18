#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to find the GCD of two numbers
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

// Function to find the GCD string
char *gcdOfStrings(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int gcdLen = gcd(len1, len2);

    // Create a candidate GCD string from str1
    char *candidate = (char *)malloc((gcdLen + 1) * sizeof(char));
    strncpy(candidate, str1, gcdLen);
    candidate[gcdLen] = '\0';

    // Helper function to check if str can be formed by repeating sub
    int canForm(char *str, char *sub)
    {
        int lenStr = strlen(str);
        int lenSub = strlen(sub);
        for (int i = 0; i < lenStr; i += lenSub)
        {
            if (strncmp(str + i, sub, lenSub) != 0)
            {
                return 0;
            }
        }
        return 1;
    }

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
    char str1[] = "ABCABC";
    char str2[] = "ABC";

    char *result = gcdOfStrings(str1, str2);
    printf("GCD of strings: %s\n", result);

    // If memory was allocated for result, it should be freed. In this example, it's fine to let it be because result points to a string literal when there's no common divisor.
    return 0;
}
