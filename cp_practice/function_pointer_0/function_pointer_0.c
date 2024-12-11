#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int main()
{
    int a = 10;
    int b = 20;
    int result = 0;
    int (*func)(int, int);

    func = &add;
    result = func(a, b);
    printf("Addition: %d\n", result);

    func = sub;
    result = func(a, b);
    printf("Sub: %d\n", result);

}