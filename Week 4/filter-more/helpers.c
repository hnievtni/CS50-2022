#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avarage = round(((double) image[i][j].rgbtRed + (double) image[i][j].rgbtGreen + (double) image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtRed = avarage;
            image[i][j].rgbtBlue = avarage;
            image[i][j].rgbtGreen = avarage;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2 ; j++)
        {
            int index = width - j - 1;
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][index];
            image[i][index] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double sum_red = 0, sum_blue = 0, sum_green = 0;
            int pixelCount = 0;;

            for (int icount = i - 1; icount < i + 2; icount++)
            {
                for (int jcount = j - 1; jcount < j + 2; jcount++)
                {
                    if (icount >= 0 && jcount >= 0 && icount < height && jcount < width)
                    {
                        sum_red += temp[icount][jcount].rgbtRed;
                        sum_blue += temp[icount][jcount].rgbtBlue;
                        sum_green += temp[icount][jcount].rgbtGreen;

                        pixelCount++;
                    }
                }
            }

            image[i][j].rgbtRed = round(sum_red / pixelCount);
            image[i][j].rgbtBlue = round(sum_blue / pixelCount);
            image[i][j].rgbtGreen = round(sum_green / pixelCount);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int GX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int GY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double GX_red = 0, GX_blue = 0, GX_green = 0;
            double GY_red = 0, GY_blue = 0, GY_green = 0;

            int row = 0;

            for (int icount = i - 1; icount < i + 2; icount++)
            {
                int column = 0;

                for (int jcount = j - 1; jcount < j + 2; jcount++)
                {
                    if (icount >= 0 && jcount >= 0 && icount < height && jcount < width)
                    {
                        GX_red += temp[icount][jcount].rgbtRed * GX[row][column];
                        GX_blue += temp[icount][jcount].rgbtBlue * GX[row][column];
                        GX_green += temp[icount][jcount].rgbtGreen * GX[row][column];

                        GY_red += temp[icount][jcount].rgbtRed * GY[row][column];
                        GY_blue += temp[icount][jcount].rgbtBlue * GY[row][column];
                        GY_green += temp[icount][jcount].rgbtGreen * GY[row][column];
                    }
                    column++;
                }
                row++;
            }

            int red = round(sqrt(pow(GX_red, 2) + pow(GY_red, 2)));
            int blue = round(sqrt(pow(GX_blue, 2) + pow(GY_blue, 2)));
            int green = round(sqrt(pow(GX_green, 2) + pow(GY_green, 2)));

            if (red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = red;
            }
            if (blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = blue;
            }
            if (green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = green;
            }
        }
    }
    return;
}
