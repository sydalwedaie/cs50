/*
get input: positive integer
if n=1, stop and return counter
else if n even > n/2
else if n odd > 3n + 1
*/

#include <cs50.h>
#include <stdio.h>

int collatz(int n, int steps);

int main(void)
{
    int n;
    do
    {
        n = get_int("Enter number: ");
    }
    while (n < 1);

    printf("Steps: %i\n", collatz(n, 0));
}

int collatz(int n, int steps)
{
    if (n == 1)
    {
        return steps;
    }
    else if (n % 2 == 0)
    {
        return collatz(n/2, steps + 1);
    }
    else
    {
        return collatz(3 * n + 1, steps + 1);
    }
}