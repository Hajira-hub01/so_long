#include <stdio.h>
void swap(int a, int b)
{
    int temp;

    temp = a;
    a = b;
    b = temp;

    printf("%d, %d\n", a, b);
}

int main(void)
{
    int a = 1;
    int b = 2;
    swap(a, b);
    printf("%d, %d\n", a, b);
}