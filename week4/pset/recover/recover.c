#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FORENSIC-IMAGE.\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("File %s cannot be opened.\n", argv[1]);
        return 1;
    }


    // variables used inside the loop to keep track of opened files
    int file_counter = 0;
    int file_opened = 0;
    char file_name[8];
    FILE *output;

    BYTE buffer[BLOCK_SIZE];

    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // in each iteration, we check the first three bytes for the signiture
        int is_jpg_sig = buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255;

        // there will be three branches:
        // sig is found and file is closed: open a new file and write current block
        if (is_jpg_sig && !file_opened)
        {
            if (file_counter < 10)
            {
                sprintf(file_name, "00%i.jpg", file_counter);
            }
            else
            {
                sprintf(file_name, "0%i.jpg", file_counter);
            }
            file_counter++;
            file_opened = 1;

            output = fopen(file_name, "w");
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }
        // sig is not found but file is open: write the current block to the open file
        else if (!is_jpg_sig && file_opened)
        {
            fwrite(buffer, 1, BLOCK_SIZE, output);
        }
        // sig is found and file is open: a new image is found so close the previous file
        else if (is_jpg_sig && file_opened)
        {
            fclose(output);
            file_opened = 0;
            // go back one block to make the next iteration right the signiture block to new file
            fseek(input, -BLOCK_SIZE, SEEK_CUR);
        }
    }
    // output is never closed if the last branch is not run, so we close it explicitly after the loop
    fclose(output);
    fclose(input);
}