#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PLATE_NUM_LEN 6
#define NUM_OF_PLATES 8

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    // one extra place to store the NUL terminator
    char buffer[PLATE_NUM_LEN + 1];

    // Create array to store plate numbers
    // so this will be like an array of arrays
    char *plates[NUM_OF_PLATES];

    FILE *infile = fopen(argv[1], "r");

    for (int i = 0; i < NUM_OF_PLATES; i++)
    {
        fread(buffer, 1, PLATE_NUM_LEN + 1, infile);
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // allocate enough memory for each string in the plates array
        plates[i] = malloc(PLATE_NUM_LEN + 1);

        // Save plate number in array
        strcpy(plates[i], buffer);

        printf("%s\n", plates[i]);

        free(plates[i]);
    }
}
