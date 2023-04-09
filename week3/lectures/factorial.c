#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

long factorial(int num);

int main(int argc, string argv[])
{
    int num = atoi(argv[1]);
    printf("%i! is %li\n", num, factorial(num));
}

long factorial(int num)
{
    if (num == 1)
    {
        return 1;
    }
    return num * factorial(num -1);
}