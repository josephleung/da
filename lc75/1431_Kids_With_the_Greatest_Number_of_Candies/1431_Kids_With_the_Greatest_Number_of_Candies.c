#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int *kidsWithCandies(int *candies, int candiesSize, int extraCandies, int *returnSize)
{
    int maxCandies = 0;
    for (int i = 0; i < candiesSize; i++)
    {
        if (candies[i] > maxCandies)
        {
            maxCandies = candies[i];
        }
    }

    int *result = (int *)malloc(candiesSize * sizeof(int));
    for (int i = 0; i < candiesSize; i++)
    {
        result[i] = (candies[i] + extraCandies >= maxCandies) ? 1 : 0;
    }

    *returnSize = candiesSize;
    return result;
}

int main()
{
    int candies[] = {2, 3, 5, 1, 3};
    int candiesSize = 5;
    int extraCandies = 3;
    int returnSize;
    int *result = kidsWithCandies(candies, candiesSize, extraCandies, &returnSize);

    printf("Result: ");
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}