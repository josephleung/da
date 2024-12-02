#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void productExceptSelf(int *nums, int numsSize, int *returnSize, int **returnArray)
{
    *returnSize = numsSize;
    *returnArray = (int *)malloc(numsSize * sizeof(int));

    int *leftProducts = (int *)malloc(numsSize * sizeof(int));
    int *rightProducts = (int *)malloc(numsSize * sizeof(int));

    leftProducts[0] = 1;
    for (int i = 1; i < numsSize; i++)
    {
        leftProducts[i] = leftProducts[i - 1] * nums[i - 1];
    }

    rightProducts[numsSize - 1] = 1;
    for (int i = numsSize - 2; i >= 0; i--)
    {
        rightProducts[i] = rightProducts[i + 1] * nums[i + 1];
    }

    for (int i = 0; i < numsSize; i++)
    {
        (*returnArray)[i] = leftProducts[i] * rightProducts[i];
    }

    free(leftProducts);
    free(rightProducts);
}

int main()
{
    int nums[] = {1, 2, 3, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    int *returnArray;

    productExceptSelf(nums, numsSize, &returnSize, &returnArray);

    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", returnArray[i]);
    }
    printf("\n");

    free(returnArray);
    return 0;
}

