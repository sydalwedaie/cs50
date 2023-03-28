// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool has_lower = false;
    bool has_upper = false;
    bool has_digit = false;
    bool has_symbol = false;

    int password_length = strlen(password);

    for (int i = 0; i < password_length; i++)
    {
        char current_char = password[i];
        if (islower(current_char))
        {
            has_lower = true;
        }
        else if (isupper(current_char))
        {
            has_upper = true;
        }
        else if (isdigit(current_char))
        {
            has_digit = true;
        }
        else if (ispunct(current_char))
        {
            has_symbol = true;
        }
    }

    return (has_lower && has_upper && has_digit && has_symbol);
}
