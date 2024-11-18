#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char * mergeAlternately(char * word1, char * word2){
    int len1 = strlen(word1);
    int len2 = strlen(word2);
    int len_merged = len1 + len2;
    char* merged = (char*) malloc(len_merged + 1);
    int i = 0, j = 0, k = 0;

    while(i < len1 || j < len2)
    {
        if(i < len1)
        {
            merged[k++] = word1[i++];
        }
        if(j < len2)
        {
            merged[k++] = word2[j++];
        }
    }

    merged[k] = '\0';

    return merged;
}

int main()
{
    char word1_0[10] = "abc";
    char word2_0[10] = "pqr";
    char* merged = mergeAlternately(word1_0, word2_0);
    printf("Merged string: %s\n", merged);


    char word1_1[] = "ab";
    char word2_1[] = "pqrs";
    merged = mergeAlternately(word1_1, word2_1);
    printf("Merged string: %s\n", merged);


    strcpy(word1_0, "abcd");
    strcpy(word2_0, "pq");
    merged = mergeAlternately(word1_0, word2_0);
    printf("Merged string: %s\n", merged);

    return 0;

}