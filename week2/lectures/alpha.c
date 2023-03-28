#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    string str = argv[1];
    int str_length = strlen(str);

    for (int i = 1; i < str_length; i++)
    {
        if (str[i-1] > str[i])
        {
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
}