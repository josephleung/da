#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int is_vowel(char c)
{
    if (c == 'a' || c == 'A' || c == 'e' || c == 'E' ||
        c == 'i' || c == 'I' || c == 'o' || c == 'O' ||
        c == 'u' || c == 'U')
        return true;
    else
        return false;
}

void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

#if 0
char *reverseVowels(char *s)
{
    unsigned int str_len = strlen(s);
    int i = 0;
    int j = str_len - 1;
    char temp;

    printf("str_len=%d\n", str_len);
    for (i = 0, j = str_len - 1; i < j; i++, j--)
    {
        printf("i=%d, j=%d\n", i, j);
        if(is_vowel(s[i]) && is_vowel(s[j]))
        {
            temp = s[i];
            s[i] = s[j];
            s[j] = temp;
        }
        else if(is_vowel(s[i]) && !is_vowel(s[j]))
        {
            i--;
        }
        else if(!is_vowel(s[i]) && is_vowel(s[j]))
        {
            j++;
        }
        printf("i=%d, j=%d\n\n", i, j);
    }
    return s;
}

#else
char *reverseVowels(char *s)
{
    int left = 0;
    int right = strlen(s) - 1;
    
    while(left < right)
    {
        //find the next vowel from the left
        while(left < right && !is_vowel(s[left]))
        {
            left++;
        }

        //find the next vowel from the right
        while(left < right && !is_vowel(s[right]))
        {
            right--;
        }

        //swap the vowel
        if(left < right)
        {
            swap(&s[left], &s[right]);
            left++;
            right--;
        }
    }
    return s;
}

#endif

int main()
{
    char test[] = "IceCreAm";  //AceCreIm
    printf("%s\n", test);
    printf("%s\n", reverseVowels(test));
    return 0;
}