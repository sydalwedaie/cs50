#include <cs50.h>
#include <stdio.h>

int main(void) {
    string name = get_string("Enter name: ");
    int age = get_int("Enter age: ");
    string number = get_string("Enter number: ");

    printf("---------\n");
    printf("Your name is %s. You are %i years old and can be contacted at %s\n", name, age, number);
}