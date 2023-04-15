#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];
            int average = round((pixel->rgbtBlue + pixel->rgbtGreen + pixel->rgbtRed) / 3.0);
            pixel->rgbtBlue = average;
            pixel->rgbtGreen = average;
            pixel->rgbtRed = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];

            int originalRed = pixel->rgbtRed;
            int originalGreen = pixel->rgbtGreen;
            int originalBlue = pixel->rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            pixel->rgbtBlue = sepiaBlue < 255 ? sepiaBlue : 255;
            pixel->rgbtGreen = sepiaGreen < 255 ? sepiaGreen : 255;
            pixel->rgbtRed = sepiaRed < 255 ? sepiaRed : 255;

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE *left_pixel = &image[i][j];
            RGBTRIPLE *right_pixel = &image[i][width - j - 1];
            RGBTRIPLE tmp_pixel = *left_pixel;

            *left_pixel = *right_pixel;
            *right_pixel = tmp_pixel;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make a copy of the image, to be used in the loop
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    // loop over the image, pixel by pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // save a pointer to the current pixel of the original image
            RGBTRIPLE *pixel = &image[i][j];

            // save each adjacent pixel from the copy
            RGBTRIPLE box_1 = image_copy[i - 1][j - 1];
            RGBTRIPLE box_2 = image_copy[i - 1][j];
            RGBTRIPLE box_3 = image_copy[i - 1][j + 1];
            RGBTRIPLE box_4 = image_copy[i][j - 1];
            RGBTRIPLE box_5 = image_copy[i][j];
            RGBTRIPLE box_6 = image_copy[i][j + 1];
            RGBTRIPLE box_7 = image_copy[i + 1][j - 1];
            RGBTRIPLE box_8 = image_copy[i + 1][j];
            RGBTRIPLE box_9 = image_copy[i + 1][j + 1];

            int valid_box_count = 0;
            int total_blue = 0;
            int total_green = 0;
            int total_red = 0;

            // add middle row to total values
            // middle pixel
            valid_box_count++;
            total_blue += box_5.rgbtBlue;
            total_green += box_5.rgbtGreen;
            total_red += box_5.rgbtRed;

            if (j - 1 > -1)
            {
                // left pixel
                valid_box_count++;
                total_blue += box_4.rgbtBlue;
                total_green += box_4.rgbtGreen;
                total_red += box_4.rgbtRed;
            }

            if (j + 1 < width)
            {
                // right pixel
                valid_box_count++;
                total_blue += box_6.rgbtBlue;
                total_green += box_6.rgbtGreen;
                total_red += box_6.rgbtRed;
            }

            // add top row to total values
            if (i - 1 > -1)
            {
                // top pixel
                valid_box_count++;
                total_blue += box_2.rgbtBlue;
                total_green += box_2.rgbtGreen;
                total_red += box_2.rgbtRed;

                if (j - 1 > -1)
                {
                    // top left
                    valid_box_count++;
                    total_blue += box_1.rgbtBlue;
                    total_green += box_1.rgbtGreen;
                    total_red += box_1.rgbtRed;
                }

                if (j + 1 < width)
                {
                    // top right
                    valid_box_count++;
                    total_blue += box_3.rgbtBlue;
                    total_green += box_3.rgbtGreen;
                    total_red += box_3.rgbtRed;
                }
            }

            // add bottom row
            if (i + 1 < height)
            {
                // bottom pixel
                valid_box_count++;
                total_blue += box_8.rgbtBlue;
                total_green += box_8.rgbtGreen;
                total_red += box_8.rgbtRed;

                if (j - 1 > -1)
                {
                    // bottom left
                    valid_box_count++;
                    total_blue += box_7.rgbtBlue;
                    total_green += box_7.rgbtGreen;
                    total_red += box_7.rgbtRed;
                }

                if (j + 1 < width)
                {
                    // bottom right
                    valid_box_count++;
                    total_blue += box_9.rgbtBlue;
                    total_green += box_9.rgbtGreen;
                    total_red += box_9.rgbtRed;
                }
            }

            // average the total values to the nearest integer
            int average_blue = round(total_blue / (float) valid_box_count);
            int average_green = round(total_green / (float) valid_box_count);
            int average_red = round(total_red / (float) valid_box_count);

            // update the values of the original image
            pixel->rgbtBlue = average_blue;
            pixel->rgbtGreen = average_green;
            pixel->rgbtRed = average_red;
        }
    }
}
