#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool increasingTriplet(int *nums, int numsSize)
{
    int first = INT_MAX;
    int second = INT_MAX;

    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] <= first)
        {
            first = nums[i];
        }
        else if (nums[i] <= second)
        {
            second = nums[i];
        }
        else
        {
            return true;
        }
    }

    return false;
}

int main()
{
    int nums[] = {2,1,5,0,4,6};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    if (increasingTriplet(nums, numsSize))
    {
        printf("The array contains an increasing triplet.\n");
    }
    else
    {
        printf("The array does not contain an increasing triplet.\n");
    }
    printf("int: %d.\n", INT_MAX);
    printf("hex: 0x%x.\n", INT_MAX);
}