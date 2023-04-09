#include <stdio.h>

int main(void)
{
    char *s = "Hello Hello there";
    char *t = "Hello Hello there";

    printf("This is the 1st character: %c\n", *s);
    printf("This is the 2nd character: %c\n", *(s+1));

    printf("This is the 1st char's address: %p\n", s);
    printf("This is the 2nd char's address: %p\n", s+1);

    printf("This is the whole string: %s\n", s);
    printf("This is a substring: %s\n", s+1);

    printf("What's this? %p\n", &s);

    printf("Whay aren't these equal? s is stored in %p but t in %p\n", s, t);

    if (s == t)
    {
        printf("Same\n");
    }
    else
    {
        printf("Different\n");
    }

}