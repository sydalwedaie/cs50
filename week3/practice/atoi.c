#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int input_len = strlen(input);

    // base case
    if (input_len == 0)
    {
        return 0;
    }

    // get the last character, and subract 48 or '0' to get the equivalent int.
    int last_digit = input[input_len - 1] - '0';

    // remove the last character
    input[input_len - 1] = '\0';

    // build the number, starting from the least significant figre.
    return last_digit + 10 * convert(input);
}