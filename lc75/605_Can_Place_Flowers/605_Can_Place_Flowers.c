#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n)
{
    int count = 0;
    for (int i = 0; i < flowerbedSize; i++)
    {
        if (flowerbed[i] == 0)
        {
            int prev = (i == 0) ? 0 : flowerbed[i - 1];
            int next = (i == flowerbedSize - 1) ? 0 : flowerbed[i + 1];
            if (prev == 0 && next == 0)
            {
                flowerbed[i] = 1;
                count++;
                if (count >= n)
                {
                    return true;
                }
            }
        }
    }
    return count >= n;
}

int main()
{
    int flowerbed1[] = {1, 0, 0, 0, 1};
    int flowerbedSize1 = 5;
    int n1 = 1;
    printf("Can place flowers: %s\n", canPlaceFlowers(flowerbed1, flowerbedSize1, n1) ? "true" : "false");

    int flowerbed2[] = {1, 0, 0, 0, 1};
    int flowerbedSize2 = 5;
    int n2 = 2;
    printf("Can place flowers: %s\n", canPlaceFlowers(flowerbed2, flowerbedSize2, n2) ? "true" : "false");

    return 0;
}