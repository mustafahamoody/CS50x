/*
References
Everything about the color Yellow. (n.d.). Canva. Retrieved July 24, 2023, from https://www.canva.com/colors/color-meanings/yellow/
*/

#include "helpers.h"

#define pixel image[i][j]

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (pixel.rgbtRed == 0x00 && pixel.rgbtGreen == 0x00 && pixel.rgbtBlue == 0x00)
            {
                pixel.rgbtRed = 0xFF;
                pixel.rgbtGreen = 0xFF;
            }
        }
    }
}
