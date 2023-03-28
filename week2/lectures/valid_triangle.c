#include <cs50.h>
#include <stdio.h>

bool valid_triangle(float a, float b, float c);

int main(void)
{
    int a, b, c;

    do
    {
        a = get_int("Enter side a: ");
    }
    while (a < 1);

    do
    {
        b = get_int("Enter side b: ");
    }
    while (a < 1);

    do
    {
        c = get_int("Enter side c: ");
    }
    while (a < 1);

    bool is_valid_triangle = valid_triangle(a, b, c);

    printf("This %s a valid triangle.", is_valid_triangle ? "is" : "is NOT");
}

bool valid_triangle(float a, float b, float c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return false;
    }
    if (a + b <= c || a + c <= b || b + c <= a)
    {
        return false;
    }
    return true;
}