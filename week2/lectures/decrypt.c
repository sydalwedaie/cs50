#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    string msg = "UIJT XBT DT50";
    int key = -1;

    for (int i = 0, length = strlen(msg); i < length; i++)
    {
        if (msg[i] > 65)
        {
            printf("%c", msg[i] - 1);
        }
        else if (msg[i] == 32)
        {
            printf(" ");
        }
        else
        {
            printf("%c", msg[i]);
        }
    }
    printf("\n");
}