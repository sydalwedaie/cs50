#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Get the user's name
    string name = get_string("What's your name? ");
    // Print a personalized greeting
    printf("Hello, %s!\n", name);
}