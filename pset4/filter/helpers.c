#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;          // Float variable to calculate the average value of colors
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = (float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = (int)round(avg);
            image[i][j].rgbtGreen = (int)round(avg);
            image[i][j].rgbtRed = (int)round(avg);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int k;
    RGBTRIPLE temp;         // Temporary struct to store a pixel value
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, x = width / 2; j < x; j++)
        {
            k = width - j - 1;       // Determining swap position
            temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float avgRed, avgGreen, avgBlue;       // Float variables to calculate average of colors in a pixel
    int x = width - 1, y = height - 1;
    RGBTRIPLE temp[height][width];         // Temporary array to store new pixel values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)                   // For the first row
            {
                if (j == 0)               // For the first pixel in the row
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) /
                               4;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4;

                    // Storing new values in temp array
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
                else if (j == x)    // For the last pixel in the row
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) /
                               4;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4;

                    // Storing new values in temp array
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
                else          // For the middle pixels in the row
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j
                                     - 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                                       image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i +
                                      1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;

                    // Storing new values in temp array
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
            }

            else if (i == y)   // For the last row
            {
                if (j == 0)             // For the first pixel in the row
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) /
                               4;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4;

                    // Storing new values in temp array
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
                else if (j == x)  // For the last pixel in the row
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) /
                               4;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4;

                    // Storing new values in temp array
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
                else           // For the middle pixels in the row
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j
                                     - 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                       image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i -
                                      1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6;

                    // Storing new values in temp array
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
            }

            else        // For middle rows
            {
                if (j == 0)             // For the first pixel in the row
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i +
                                     1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                       image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                      image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;

                    // Storing new values in temp array
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
                else if (j == x)  // For the last pixel in the row
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i +
                                     1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                       image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                      image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6;

                    // Storing new values in temp array
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
                else           // For the middle pixels in the row
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j
                                     - 1].rgbtRed + image[i - 1][j + 1].rgbtRed  + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed) /
                             9;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                       image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i
                                               + 1][j + 1].rgbtGreen) / 9;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i
                                      - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j +
                                              1].rgbtBlue) / 9;

                    // Storing new values in temp array
                    temp[i][j].rgbtRed = (int)round(avgRed);
                    temp[i][j].rgbtGreen = (int)round(avgGreen);
                    temp[i][j].rgbtBlue = (int)round(avgBlue);
                }
            }
        }
    }

    // Assigning new values to the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    float GxRed, GxGreen, GxBlue, GyRed, GyGreen, GyBlue;
    int x = width - 1, y = height - 1;
    int red[height][width], green[height][width], blue[height][width];         // Temporary array to store new pixel values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)                   // For the first row
            {
                if (j == 0)               // For the first pixel in first row
                {
                    GxRed = (float)(image[i][j + 1].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed);
                    GxGreen = (float)(image[i][j + 1].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen);
                    GxBlue = (float)(image[i][j + 1].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue);
                    GyRed = (float)(image[i + 1][j].rgbtRed * 2 + image[i + 1][j + 1].rgbtRed);
                    GyGreen = (float)(image[i + 1][j].rgbtGreen * 2 + image[i + 1][j + 1].rgbtGreen);
                    GyBlue = (float)(image[i + 1][j].rgbtBlue * 2 + image[i + 1][j + 1].rgbtBlue);

                    // Storing new values in temp array
                    red[i][j] = (int)round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                    green[i][j] = (int)round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                    blue[i][j] = (int)round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }
                else if (j == x)    // For the last pixel in first row
                {
                    GxRed = (float)(image[i][j - 1].rgbtRed * (-2) + image[i + 1][j - 1].rgbtRed * (-1));
                    GxGreen = (float)(image[i][j - 1].rgbtGreen * (-2) + image[i + 1][j - 1].rgbtGreen * (-1));
                    GxBlue = (float)(image[i][j - 1].rgbtBlue * (-2) + image[i + 1][j - 1].rgbtBlue) * (-1);
                    GyRed = (float)(image[i + 1][j].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed);
                    GyGreen = (float)(image[i + 1][j].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen);
                    GyBlue = (float)(image[i + 1][j].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue);

                    // Storing new values in temp array
                    red[i][j] = (int)round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                    green[i][j] = (int)round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                    blue[i][j] = (int)round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }
                else          // For the middle pixels in first row
                {
                    GxRed = (float)(image[i][j - 1].rgbtRed * (-2) + image[i][j + 1].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed *
                                    (-1) + image[i + 1][j + 1].rgbtRed);
                    GxGreen = (float)(image[i][j - 1].rgbtGreen * (-2) + image[i][j + 1].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen *
                                      (-1) + image[i + 1][j + 1].rgbtGreen);
                    GxBlue = (float)(image[i][j - 1].rgbtBlue * (-2) + image[i][j + 1].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue *
                                     (-1) + image[i + 1][j + 1].rgbtBlue);
                    GyRed = (float)(image[i + 1][j].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed);
                    GyGreen = (float)(image[i + 1][j].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen);
                    GyBlue = (float)(image[i + 1][j].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue);

                    // Storing new values in temp array
                    red[i][j] = (int)round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                    green[i][j] = (int)round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                    blue[i][j] = (int)round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }
            }

            else if (i == y)   // For the last row
            {
                if (j == 0)             // For the first pixel in last row
                {
                    GxRed = (float)(image[i][j + 1].rgbtRed * 2 + image[i - 1][j + 1].rgbtRed);
                    GxGreen = (float)(image[i][j + 1].rgbtGreen * 2 + image[i - 1][j + 1].rgbtGreen);
                    GxBlue = (float)(image[i][j + 1].rgbtBlue * 2 + image[i - 1][j + 1].rgbtBlue);
                    GyRed = (float)(image[i - 1][j].rgbtRed * (-2) + image[i - 1][j + 1].rgbtRed * (-1));
                    GyGreen = (float)(image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j + 1].rgbtGreen * (-1));
                    GyBlue = (float)(image[i - 1][j].rgbtBlue * (-2) + image[i - 1][j + 1].rgbtBlue * (-1));

                    // Storing new values in temp array
                    red[i][j] = (int)round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                    green[i][j] = (int)round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                    blue[i][j] = (int)round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }
                else if (j == x)  // For the last pixel in last row
                {
                    GxRed = (float)(image[i][j - 1].rgbtRed * (-2) + image[i - 1][j - 1].rgbtRed * (-1));
                    GxGreen = (float)(image[i][j - 1].rgbtGreen * (-2) + image[i - 1][j - 1].rgbtGreen * (-1));
                    GxBlue = (float)(image[i][j - 1].rgbtBlue * (-2) + image[i - 1][j - 1].rgbtBlue * (-1));
                    GyRed = (float)(image[i - 1][j].rgbtRed * (-2) + image[i - 1][j - 1].rgbtRed * (-1));
                    GyGreen = (float)(image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j - 1].rgbtGreen * (-1));
                    GyBlue = (float)(image[i - 1][j].rgbtBlue * (-2) + image[i - 1][j - 1].rgbtBlue * (-1));

                    // Storing new values in temp array
                    red[i][j] = (int)round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                    green[i][j] = (int)round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                    blue[i][j] = (int)round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }
                else           // For the middle pixels in last row
                {
                    GxRed = (float)(image[i][j - 1].rgbtRed * (-2) + image[i][j + 1].rgbtRed * 2 + image[i - 1][j - 1].rgbtRed *
                                    (-1) + image[i - 1][j + 1].rgbtRed);
                    GxGreen = (float)(image[i][j - 1].rgbtGreen * (-2) + image[i][j + 1].rgbtGreen * 2 + image[i - 1][j - 1].rgbtGreen *
                                      (-1) + image[i - 1][j + 1].rgbtGreen);
                    GxBlue = (float)(image[i][j - 1].rgbtBlue * (-2) + image[i][j + 1].rgbtBlue * 2 + image[i - 1][j - 1].rgbtBlue *
                                     (-1) + image[i - 1][j + 1].rgbtBlue);
                    GyRed = (float)(image[i - 1][j].rgbtRed * (-2) + image[i - 1][j - 1].rgbtRed * (-1) + image[i - 1][j + 1].rgbtRed * (-1));
                    GyGreen = (float)(image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j - 1].rgbtGreen * (-1) + image[i - 1][j + 1].rgbtGreen * (-1));
                    GyBlue = (float)(image[i - 1][j].rgbtBlue * (-2) + image[i - 1][j - 1].rgbtBlue * (-1) + image[i - 1][j + 1].rgbtBlue * (-1));

                    // Storing new values in temp array
                    red[i][j] = (int)round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                    green[i][j] = (int)round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                    blue[i][j] = (int)round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }
            }

            else        // For middle rows
            {
                if (j == 0)             // For the first pixel in middle rows
                {
                    GxRed = (float)(image[i][j + 1].rgbtRed * 2 + image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed);
                    GxGreen = (float)(image[i][j + 1].rgbtGreen * 2 + image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen);
                    GxBlue = (float)(image[i][j + 1].rgbtBlue * 2 + image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue);
                    GyRed = (float)(image[i - 1][j].rgbtRed * (-2) + image[i - 1][j + 1].rgbtRed * (-1) + image[i + 1][j].rgbtRed * 2 + image[i + 1][j +
                                    1].rgbtRed);
                    GyGreen = (float)(image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j + 1].rgbtGreen * (-1) + image[i + 1][j].rgbtGreen * 2 + image[i
                                      + 1][j + 1].rgbtGreen);
                    GyBlue = (float)(image[i - 1][j].rgbtBlue * (-2) + image[i - 1][j + 1].rgbtBlue * (-1) + image[i + 1][j].rgbtBlue * 2 + image[i +
                                     1][j + 1].rgbtBlue);

                    // Storing new values in temp array
                    red[i][j] = (int)round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                    green[i][j] = (int)round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                    blue[i][j] = (int)round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }
                else if (j == x)  // For the last pixel in middle rows
                {
                    GxRed = (float)(image[i][j - 1].rgbtRed * (-2) + image[i - 1][j - 1].rgbtRed * (-1) + image[i + 1][j - 1].rgbtRed * (-1));
                    GxGreen = (float)(image[i][j - 1].rgbtGreen * (-2) + image[i - 1][j - 1].rgbtGreen * (-1) + image[i + 1][j - 1].rgbtGreen * (-1));
                    GxBlue = (float)(image[i][j - 1].rgbtBlue * (-2) + image[i - 1][j - 1].rgbtBlue * (-1) + image[i + 1][j - 1].rgbtBlue * (-1));
                    GyRed = (float)(image[i - 1][j].rgbtRed * (-2) + image[i - 1][j - 1].rgbtRed * (-1) + image[i + 1][j].rgbtRed * 2 + image[i + 1][j -
                                    1].rgbtRed);
                    GyGreen = (float)(image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j - 1].rgbtGreen * (-1) + image[i + 1][j].rgbtGreen * 2 + image[i
                                      + 1][j - 1].rgbtGreen);
                    GyBlue = (float)(image[i - 1][j].rgbtBlue * (-2) + image[i - 1][j - 1].rgbtBlue * (-1) + image[i + 1][j].rgbtBlue * 2 + image[i +
                                     1][j - 1].rgbtBlue);

                    // Storing new values in temp array
                    red[i][j] = (int)round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                    green[i][j] = (int)round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                    blue[i][j] = (int)round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }
                else           // For the middle pixels in middle rows
                {
                    GxRed = (float)(image[i][j - 1].rgbtRed * (-2) + image[i][j + 1].rgbtRed * 2 + image[i - 1][j - 1].rgbtRed *
                                    (-1) + image[i - 1][j + 1].rgbtRed  + image[i + 1][j - 1].rgbtRed * (-1) + image[i + 1][j + 1].rgbtRed);
                    GxGreen = (float)(image[i][j - 1].rgbtGreen * (-2) + image[i][j + 1].rgbtGreen * 2 + image[i - 1][j - 1].rgbtGreen *
                                      (-1) + image[i - 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen * (-1) + image[i + 1][j + 1].rgbtGreen);
                    GxBlue = (float)(image[i][j - 1].rgbtBlue * (-2) + image[i][j + 1].rgbtBlue * 2 + image[i - 1][j - 1].rgbtBlue *
                                     (-1) + image[i - 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue * (-1) + image[i + 1][j + 1].rgbtBlue);
                    GyRed = (float)(image[i - 1][j].rgbtRed * (-2) + image[i - 1][j - 1].rgbtRed * (-1) + image[i - 1][j + 1].rgbtRed *
                                    (-1)  + image[i + 1][j].rgbtRed * 2 + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed);
                    GyGreen = (float)(image[i - 1][j].rgbtGreen * (-2) + image[i - 1][j - 1].rgbtGreen * (-1) + image[i - 1][j + 1].rgbtGreen *
                                      (-1) + image[i + 1][j].rgbtGreen * 2 + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen);
                    GyBlue = (float)(image[i - 1][j].rgbtBlue * (-2) + image[i - 1][j - 1].rgbtBlue * (-1) + image[i - 1][j + 1].rgbtBlue *
                                     (-1) + image[i + 1][j].rgbtBlue * 2 + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue);

                    // Storing new values in temp array
                    red[i][j] = (int)round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
                    green[i][j] = (int)round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));
                    blue[i][j] = (int)round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
                }
            }
        }
    }

    // Assigning new values to the pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (red[i][j] > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = red[i][j];
            }
            if (green[i][j] > 255)\
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = green[i][j];
            }
            if (blue[i][j] > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = blue[i][j];
            }
        }
    }
    return;
}
