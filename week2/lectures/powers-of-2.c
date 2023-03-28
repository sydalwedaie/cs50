#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int size;
    do
    {
        size = get_int("Enter size: ");
    }
    while (size < 1);

    int powers[size];
    powers[0] = 1;

    for(int i = 0; i < size; i++)
    {
        powers[i+1] = 2 * powers[i];
        printf("%i\n", powers[i]);
    }

}