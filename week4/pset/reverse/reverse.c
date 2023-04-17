#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse INPUT.wav OUTPUT.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Input file %s cannot be opened.\n", argv[1]);
        return 1;
    }

    // Read header
    // TODO #3
    // WAVHEADER is a 'custom data type' defined in wav.h
    // we need this struct to save the header data from the file into a structured data.
    WAVHEADER header;
    fread(&header, sizeof(header), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(header))
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (input == NULL)
    {
        printf("Output file %s cannot be opened.\n", argv[2]);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(header), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    // each block represents a single unit of audio data.
    // we need this to iterate over the blocks
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    uint32_t audio_block;

    // seek the pointer to 'block_size' bytes to the end
    // this makes 'fread' to reach the very last block the very next time it is called
    fseek(input, -block_size, SEEK_END);

    // in each iteration, we read one block, write it to the output, and seek back 2 blocks
    // the loop continues until the pointer reaches the header section.
    // at first I had it set at 44 which is the end of the header but check50 didn't accept it.
    while (ftell(input) > 40)
    {
        fread(&audio_block, block_size, 1, input);
        fwrite(&audio_block, block_size, 1, output);
        fseek(input, -block_size * 2, SEEK_CUR);
    }

    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    // in a WAV file, header.format spells WAVE.
    char *string_to_match = "WAVE";

    // we'll compare this string with the actual data inside the header
    for (int i = 0, n = strlen(string_to_match); i < n; i++)
    {
        // if the two characters were the same, subtracting them from each other would give zero.
        // that's because doing math with characters would use their ASCII values
        if (header.format[i] - string_to_match[i] != 0)
        {
            return 0;
        }
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return (header.numChannels * (header.bitsPerSample / 8));
}