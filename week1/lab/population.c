#include <cs50.h>
#include <stdio.h>

int get_size(string prompt, int min);
int get_years(int start, int end);

int main(void)
{
    // TODO: Prompt for start size (must be 9 or greater)
    int start = get_size("Enter the start size: ", 9);

    // TODO: Prompt for end size (equal or greater than start size)
    int end = get_size("Enter the end size: ", start);

    // TODO: Calculate number of years until we reach threshold (at least the size of the end value)
    int years = get_years(start, end);

    // TODO: Print number of years (Years: n)
    printf("Years: %i\n", years);
}

int get_size(string prompt, int min)
{
    int size;
    do
    {
        size = get_int(prompt);
    }
    while (size < min);
    return size;
}

int get_years(start, end)
{
    int years = 0;
    if (start != end)
    {
        do
        {
            start = start + (start / 3) - (start / 4);
            years++;
        }
        while (start < end);
    }
    return years;
}
