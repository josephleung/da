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
    char word1[10] = "abc";
    char word2[10] = "pqr";
    char* merged = mergeAlternately(word1, word2);
    printf("Merged string: %s\n", merged);

    strcpy(word1, "ab");
    strcpy(word2, "pqrs");
    merged = mergeAlternately(word1, word2);
    printf("Merged string: %s\n", merged);

    strcpy(word1, "abcd");
    strcpy(word2, "pq");
    merged = mergeAlternately(word1, word2);
    printf("Merged string: %s\n", merged);

    free(merged);

    return 0;

}