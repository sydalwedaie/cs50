#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_pyramid(int hight);

int main(void)
{
    int height = get_height();
    print_pyramid(height);
}

int get_height(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    return height;
}

void print_leading_spaces(int row, int height)
{
    // print a number of spaces equal to the difference
    // between the row number and height - 1
    while (row < height - 1)
    {
        printf(" ");
        row++;
    }
}

void print_row(int row)
{
    // print a number of # characters equal to the row number
    while (row >= 0)
    {
        printf("#");
        row--;
    }
}

void print_pyramid(int height)
{
    for (int row = 0; row < height; row++)
    {
        // build the left side
        print_leading_spaces(row, height);
        print_row(row);

        // separate the two sides
        printf("  ");

        // build the right side
        print_row(row);
        printf("\n");
    }
}