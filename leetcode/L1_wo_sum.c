

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    int i, j; 
    int* returnNums = (int*)malloc(sizeof(int) * numsSize);
    *returnSize = 2;
    
    for(i = 0; i < numsSize; i++)
    {
        for(j = i+1; j < numsSize; j++)
        {
            if((nums[j] + nums[i]) == target)
            {
                returnNums[0] = i;
                returnNums[1] = j;
                return returnNums;
            }

        }
    }
    return returnNums;
}