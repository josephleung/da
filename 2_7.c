#include <stdio.h>
#include <stdlib.h>

int max3(int in1, int in2, int in3)
{
	int maxout = 0;

	maxout = (in1 > in2) ? in1 : in2;
	maxout = (in3 > maxout) ? in3 : maxout;

	return maxout;
}

int maxSubSum(const int a[], int left, int right)
{
	int maxLeftSum, maxRightSum;
	int maxLeftBorderSum, maxRightBorderSum;
	int leftBorderSum, rightBorderSum;
	int center, i;

	if (left == right)
	{
		if (a[left] > 0)
			return a[left];
		else
			return 0;
	}

	center = (left + right) / 2;
	maxLeftSum = maxSubSum(a, left, center);
	maxRightSum = maxSubSum(a, center + 1, right);

	maxLeftBorderSum = 0;
	leftBorderSum = 0;
	for (i = center; i >= left; i--)
	{
		leftBorderSum += a[i];
		if (maxLeftBorderSum < leftBorderSum)
			maxLeftBorderSum = leftBorderSum;
	}

	maxRightBorderSum = 0;
	rightBorderSum = 0;
	for (i = center + 1; i <= right; i++)
	{
		rightBorderSum += a[i];
		if (maxRightBorderSum < rightBorderSum)
			maxRightBorderSum = rightBorderSum;
	}

	return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

void main()
{

	int input;
	int array[] = {3, -5, 1, 5, 10, -12, 32};
	//int input = getchar() - '0';
	scanf("%d", &input);
	if (input > (sizeof(array) / sizeof(array[0])))
	{
		printf("input %d is larger than the # of elements %d!\n", input, (int)(sizeof(array) / sizeof(array[0])));
		return;
	}
	printf("%d\n", maxSubSum(array, 0, input));

	//printf("%d\n", max3(1, 5, 4));
}
