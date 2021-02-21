#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxSubSequenceSum(const int a[], int N)
{
	int thisSum, maxSum, i;
	
	thisSum = maxSum = 0;
	for(i = 0; i < N; i++)
	{
		thisSum += a[i];
		
		if(thisSum > maxSum)
			maxSum = thisSum;
		else if(thisSum < 0)
			thisSum = 0;
	}
	return maxSum;
}

void main(int argc, char *argv[])
{
	int input;
	///////////////1   2  3  4  5   6    7
	int array[] = {3, -5, 1, 5, 10, -12, 32};
	
	int i,j;
	
	if(argc != 1)
	{
		//printf("%s\n", argv[0]); //argv[0] is the name of the program
		printf("argc: %d\n", argc);
		printf("argv[1]: %s, size:%d\n", argv[1], (int)strlen(argv[1]));
		
		
		//while(*argv[1] != '\0')
		char *c = argv[1];
		while (*c != '\0')
			printf("%c,", *c++);
		
		
		for(i = 0; i < argc; i++)
		{
			printf("\ndump argv[%d] @ %x:", i, (unsigned int)argv[i]);
			for(j = 0; j < (strlen(argv[i])); j++)
				printf("%c,", argv[i][j]);	
		}

		/*
		printf("\ndump argv[2] @ %x:", (unsigned int)&argv[2]);
		for(i = 0; i < (strlen(argv[2])); i++)
			printf("%c,", argv[2][i]);
		printf("\n");	
		*/
		
		printf("\n\n\n");
		input = (int)(argv[1][0] - '0');
	}
	else
	{
		scanf("%d", &input);	
	}

	if(input > (sizeof(array) / sizeof(array[0])))
	{
		printf("input %d is larger than the # of elements %d!\n", input, (int)(sizeof(array) / sizeof(array[0])));
		return;
	}
	printf("result:%d\n", maxSubSequenceSum(array, input));
	
	//printf("%d\n", max3(1, 5, 4));
}
