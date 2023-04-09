#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s = get_string("s: ");
    char *t = malloc(strlen(s) + 1);

    for (int i = 0, n = strlen(s) +1; i < n; i++)
    {
        t[i] = s[i];
    }

    printf("string s: %s @ is at %p\n", s, s);
    printf("string t: %s @ is at %p\n", t, t);
}