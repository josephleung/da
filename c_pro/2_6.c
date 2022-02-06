#include <stdio.h>
#include <stdlib.h>

int maxSubSequenceSum(const int a[], int N)
{
	int thisSum, maxSum, i, j;

	maxSum = 0;
	for (i = 0; i < N; i++)
	{
		thisSum = 0;
		for (j = i; j < N; j++)
		{
			thisSum += a[j];

			if (thisSum > maxSum)
				maxSum = thisSum;
		}
	}
	return maxSum;
}

int main()
{
	printf("test\n");
	int input;
	int array[] = {3, -5, 1, 5, 10, -12, 32};
	//int input = getchar() - '0';
	scanf("%d", &input);
	if (input > (sizeof(array) / sizeof(array[0])))
	{
		printf("input %d is larger than the # of elements %d!\n", input, (int)(sizeof(array) / sizeof(array[0])));
		return 1;
	}
	printf("%d\n", maxSubSequenceSum(array, input));

	return 0;
}
