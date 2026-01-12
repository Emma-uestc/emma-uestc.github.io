#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int average = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int counter = 0;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumRed += copy[ni][nj].rgbtRed;
                        sumGreen += copy[ni][j].rgbtGreen;
                        sumBlue += copy[ni][nj].rgbtBlue;
                        counter++;
                    }
                }
            }
            image[i][j].rgbtRed = round((float)sumRed / counter);
            image[i][j].rgbtGreen = round((float)sumGreen / counter);
            image[i][j].rgbtBlue = round((float)sumBlue / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float Gx_red = 0, Gx_green = 0, Gx_blue = 0;
            float Gy_red = 0, Gy_green = 0, Gy_blue = 0;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        int weightX = Gx[di + 1][dj + 1];
                        int weightY = Gy[di + 1][dj + 1];

                        Gx_red += copy[ni][nj].rgbtRed * weightX;
                        Gx_green += copy[ni][nj].rgbtGreen * weightX;
                        Gx_blue += copy[ni][nj].rgbtBlue * weightX;

                        Gy_red += copy[ni][nj].rgbtRed * weightY;
                        Gy_green += copy[ni][nj].rgbtGreen * weightY;
                        Gy_blue += copy[ni][nj].rgbtBlue * weightY;
                    }
                }
            }

            int finalRed = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int finalGreen = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int finalBlue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            if (finalRed > 255) finalRed = 255;
            if (finalGreen > 255) finalGreen = 255;
            if (finalBlue > 255) finalBlue = 255;

            image[i][j].rgbtRed = finalRed;
            image[i][j].rgbtGreen = finalGreen;
            image[i][j].rgbtBlue = finalBlue;
        }
    }
    return;
}
