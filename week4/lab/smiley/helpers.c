#include "helpers.h"
#include <stdio.h>

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    // double loop to iterate over all the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // save the reference to each pixel to a pointer
            RGBTRIPLE *pixel = &image[i][j];

            // first check if the pixel was black
            if (pixel->rgbtBlue == 0 && pixel->rgbtGreen == 0 && pixel->rgbtRed == 0)
            {
                // if yes, change the colors
                // `->` syntax to access and modify the members of RGBTRIPLE struct
                pixel->rgbtBlue = 123;
                pixel->rgbtGreen = 116;
                pixel->rgbtRed = 210;
            }
        }
    }
}
