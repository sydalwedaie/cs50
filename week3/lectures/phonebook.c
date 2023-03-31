#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    typedef struct
    {
        string name;
        string number;
    }
    person;

    person people[2];

    people[0].name = "Sayed";
    people[0].number = "+973-123123";
    people[1].name = "Ali";
    people[1].number = "+1-555-121212";

    string name = get_string("Enter name: ");

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, name) == 0)
        {
            printf("Found %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found!\n");
    return 1;
}