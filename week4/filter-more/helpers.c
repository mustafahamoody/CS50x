/*
References
Narang, P. (2022, May 30). sqrt() in C | sqrt() Function in C. Scaler. Retrieved July 25, 2023, from
https://www.scaler.com/topics/sqrt-in-c/ Narang, P. (2023, May 4). C round() Function. Scaler. Retrieved July 25, 2023, from
https://www.scaler.com/topics/c-round/
*/

#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row of pixel arrays
    for (int i = 0; i < height; i++)
    {
        // Loops through each individual pixel
        for (int j = 0; j < width; j++)
        {

            // Calculates rounded avg value of the pixels
            float avg_Urnd = (float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            int avg_Rnd = round(avg_Urnd);

            // Sets all three values to the avg rounded value of the pixels
            image[i][j].rgbtBlue = avg_Rnd;
            image[i][j].rgbtGreen = avg_Rnd;
            image[i][j].rgbtRed = avg_Rnd;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row of pixel arrays
    for (int i = 0; i < height; i++)
    {
        // Loops through each individual pixel
        for (int j = 0, n = width - 1; j < n; j++, n--)
        {
            // Swaps pixel j with pixel n
            RGBTRIPLE swap;
            swap.rgbtBlue = image[i][j].rgbtBlue;
            swap.rgbtGreen = image[i][j].rgbtGreen;
            swap.rgbtRed = image[i][j].rgbtRed;

            image[i][j] = image[i][n];

            image[i][n] = swap;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Inage Copy to store blured values
    RGBTRIPLE imgCpy[height][width];

    // Loop through each row of pixel arrays
    for (int i = 0; i < height; i++)
    {
        // Loops through each individual pixel
        for (int j = 0; j < width; j++)
        {

            // Array of unrounded avg of blue, green, red value for blur
            float avg_Urnd[] = {0.00, 0.00, 0.00};

            // Array of rounded avg of blue, green, red value for blur
            int avg_Rnd[] = {0, 0, 0};

            // Default values for m, x, top and bottom edge of grid, respectivly
            int m = -1;
            int x = 2;

            // Adjusted values for top and bottom edge
            if (i == 0)
            {
                m = 0;
            }
            else if (i == (height - 1))
            {
                x = 1;
            }

            int blocks = 0;

            // Loop for height of grid
            while (m < x)
            {
                // Default values for k, y, left and right edge of grid, respectivly
                int k = -1;
                int y = 2;

                // Adjusted values for left and right
                if (j == 0)
                {
                    k = 0;
                }
                else if (j == (width - 1))
                {
                    y = 1;
                }

                // Loop for width of grid
                while (k < y)
                {
                    // printf("%i\n", i + m);
                    // printf("%i\n", j + k);
                    // Adds current pixel value to array
                    avg_Urnd[0] += (float)image[i + m][j + k].rgbtBlue;
                    avg_Urnd[1] += (float)image[i + m][j + k].rgbtGreen;
                    avg_Urnd[2] += (float)image[i + m][j + k].rgbtRed;
                    blocks++;
                    k++;
                }
                m++;
            }

            // Divide pixel value by # of pixels
            avg_Urnd[0] /= blocks;
            avg_Urnd[1] /= blocks;
            avg_Urnd[2] /= blocks;

            // Round the values and stores in avg_Rnd array
            avg_Rnd[0] = round(avg_Urnd[0]);
            avg_Rnd[1] = round(avg_Urnd[1]);
            avg_Rnd[2] = round(avg_Urnd[2]);

            // Puts blured pixel into image copy
            imgCpy[i][j].rgbtBlue = avg_Rnd[0];
            imgCpy[i][j].rgbtGreen = avg_Rnd[1];
            imgCpy[i][j].rgbtRed = avg_Rnd[2];
        }
    }

    // Loop through each pixel and replaces original image with copy of blured image
    for (int q = 0; q < height; q++)
    {
        for (int t = 0; t < width; t++)
        {
            image[q][t] = imgCpy[q][t];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Inage Copy to store edged values
    RGBTRIPLE imgCpy[height][width];

    // Loop through each row of pixel arrays
    for (int i = 0; i < height; i++)
    {
        // Loops through each individual pixel
        for (int j = 0; j < width; j++)
        {
            // Gx values for calculation
            int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            // Gy values for calculation
            int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            // Color pixels * Gx Values
            int colorGx[] = {0, 0, 0};

            // Color pixels * Gy Values
            int colorGy[] = {0, 0, 0};

            // Unrounded edge values
            float edg_Urnd[] = {0.00, 0.00, 0.00};

            // Rounded edge values
            int edg_Rnd[] = {0, 0, 0};

            // Default values for m, x, top and bottom edge of grid, respectivly
            int m = -1;
            int x = 2;
            int h = 0;

            // Adjusted values for top and bottom edge
            if (i == 0)
            {
                m = 0;
                h = 1;
            }
            else if (i == (height - 1))
            {
                x = 1;
            }

            // Loop for height of grid
            while (m < x)
            {
                // Default values for k, y, left and right edge of grid, respectivly
                int k = -1;
                int y = 2;
                int w = 0;

                // Adjusted values for left and right
                if (j == 0)
                {
                    k = 0;
                    w = 1;
                }
                else if (j == (width - 1))
                {
                    y = 1;
                }

                // Loop for width of grid
                while (k < y)
                {
                    colorGx[0] += (Gx[h][w] * image[i + m][j + k].rgbtBlue);
                    colorGx[1] += (Gx[h][w] * image[i + m][j + k].rgbtGreen);
                    colorGx[2] += (Gx[h][w] * image[i + m][j + k].rgbtRed);

                    colorGy[0] += (Gy[h][w] * image[i + m][j + k].rgbtBlue);
                    colorGy[1] += (Gy[h][w] * image[i + m][j + k].rgbtGreen);
                    colorGy[2] += (Gy[h][w] * image[i + m][j + k].rgbtRed);
                    k++;
                    w++;
                }

                m++;
                h++;
            }

            // FOR BLUE
            //  Compute new channel value for edge
            edg_Urnd[0] = sqrt((float)((colorGx[0] * colorGx[0]) + (colorGy[0] * colorGy[0])));
            // Rounds new value
            edg_Rnd[0] = round(edg_Urnd[0]);
            // Checks if value > 255, if so caps value at 255
            if (edg_Rnd[0] > 255)
            {
                edg_Rnd[0] = 255;
            }
            // Assigns value to imageCpy
            imgCpy[i][j].rgbtBlue = edg_Rnd[0];

            // FOR GREEN
            edg_Urnd[1] = sqrt((float)((colorGx[1] * colorGx[1]) + (colorGy[1] * colorGy[1])));
            edg_Rnd[1] = round(edg_Urnd[1]);
            if (edg_Rnd[1] > 255)
            {
                edg_Rnd[1] = 255;
            }
            imgCpy[i][j].rgbtGreen = edg_Rnd[1];

            // FOR RED
            edg_Urnd[2] = sqrt((float)((colorGx[2] * colorGx[2]) + (colorGy[2] * colorGy[2])));
            edg_Rnd[2] = round(edg_Urnd[2]);
            if (edg_Rnd[2] > 255)
            {
                edg_Rnd[2] = 255;
            }
            imgCpy[i][j].rgbtRed = edg_Rnd[2];
        }
    }

    // Loop through each pixel and replaces original image with copy of edged image
    for (int q = 0; q < height; q++)
    {
        for (int t = 0; t < width; t++)
        {
            image[q][t] = imgCpy[q][t];
        }
    }
    return;
}
