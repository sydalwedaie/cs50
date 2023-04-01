// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities(void);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort_cities(void)
{
    int swap_counter = -1;

    // This condition would return false only when there was no swap left,
    // which means the array has been sorted
    while (swap_counter != 0)
    {
        swap_counter = 0;
        for (int i = 0; i < NUM_CITIES - 1; i++)
        {
            int temp_city_1 = temps[i].temp;
            string name_city_1 = temps[i].city;

            int temp_city_2 = temps[i + 1].temp;
            string name_city_2 = temps[i + 1].city;

            // comparing adjacent paris
            if (temp_city_1 < temp_city_2)
            {
                // swapping the pairs
                temps[i].temp = temp_city_2;
                temps[i].city = name_city_2;

                temps[i + 1].temp = temp_city_1;
                temps[i + 1].city = name_city_1;

                // if an entire inner loop ends without this line executing,
                // swap_counter remains zero and the outer, while loop would stop
                swap_counter++;
            }
        }
    }
}
