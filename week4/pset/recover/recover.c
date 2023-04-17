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


    int file_counter = 0;
    char file_name[8];
    // printf("%lu\n", sizeof(*output));

    BYTE buffer[BLOCK_SIZE];
    while (fread(buffer, 1, BLOCK_SIZE, input))
    {
        int is_jpg_sig = buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255;

        if (is_jpg_sig)
        {
            sprintf(file_name, "%i.jpg", file_counter);
            file_counter++;

            FILE *output = fopen(file_name, "w");

            fwrite(buffer, 1, BLOCK_SIZE, output);
            fread(buffer, 1, BLOCK_SIZE, input);
            is_jpg_sig = buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255;

            while (!is_jpg_sig && ftell(input) != -1)
            {
                fwrite(buffer, 1, BLOCK_SIZE, output);
                fread(buffer, 1, BLOCK_SIZE, input);
                is_jpg_sig = buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255;
            }

            fclose(output);
            fseek(input, -BLOCK_SIZE, SEEK_CUR);
        }

    }
}

// 255 216 255