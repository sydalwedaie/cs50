#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // create an array buffer to hold the header information
    uint8_t header_buffer[HEADER_SIZE];
    // read and write
    fread(header_buffer, 1, HEADER_SIZE, input);
    fwrite(header_buffer, 1, HEADER_SIZE, output);

    // An integer buffer to read the sample data
    // each sample will be read, saved to buffer and written to output one by one
    int16_t sample_buffer;

    // fread returns the number of items read.
    // so this loop continues until the read items becomes zero
    // note we have to pass the pointer of the buffer.
    while(fread(&sample_buffer, sizeof(int16_t), 1, input) == 1)
    {
        sample_buffer *= factor;
        fwrite(&sample_buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
