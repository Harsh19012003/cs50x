#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //greyamount initialization
    BYTE greyamount;

    //filter mechanism
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            greyamount = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = greyamount;
            image[i][j].rgbtGreen = greyamount;
            image[i][j].rgbtRed = greyamount;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE x;
    RGBTRIPLE demo[height][width];

    //copy image to demo
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width); j++)
        {
            demo[i][j] = image[i][j];
        }
    }

    //filter mechanism
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width); j++)
        {
            demo[i][j] = image[i][width - j - 1];
        }
    }

    //copy final image[][]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width); j++)
        {
            image[i][j] = demo[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //demo initialization
    RGBTRIPLE demo[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int count = 0;
            int rowCoords[] = { row - 1, row, row + 1 };
            int colCoords[] = { col - 1, col, col + 1 };
            float totalR = 0, totalG = 0, totalB = 0;

            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int curRow = rowCoords[r];
                    int curCol = colCoords[c];

                    if (curRow >= 0 && curRow < height && curCol >= 0 && curCol < width)
                    {
                        RGBTRIPLE pixel = image[curRow][curCol];

                        totalR += pixel.rgbtRed;
                        totalB += pixel.rgbtBlue;
                        totalG += pixel.rgbtGreen;

                        count++;
                    }
                }
            }
            demo[row][col].rgbtRed = round(totalR / count);
            demo[row][col].rgbtGreen = round(totalG / count);
            demo[row][col].rgbtBlue = round(totalB / count);
        }
    }

    //copy final image[][]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = demo[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //demo initialization
    RGBTRIPLE demo[height][width];

    //two 2-D arrays for sobel's operation gx and gy
    int gx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int gy[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    //iterate through each pixel
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int rowCoords[3] = { row - 1, row, row + 1 };
            int colCoords[3] = { col - 1, col, col + 1 };
            float totalRx = 0, totalGx = 0, totalBx = 0, totalRy = 0, totalGy = 0, totalBy = 0, finalR, finalG, finalB;

            //iterate through each pixel's neibouring pixel and apply sobel's operator
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    //filter mechanism
                    int curRow = rowCoords[r];
                    int curCol = colCoords[c];

                    if (curRow >= 0 && curRow < height && curCol >= 0 && curCol < width)
                    {
                        totalRx += image[curRow][curCol].rgbtRed * gx[r][c];
                        totalGx += image[curRow][curCol].rgbtGreen * gx[r][c];
                        totalBx += image[curRow][curCol].rgbtBlue * gx[r][c];

                        totalRy += image[curRow][curCol].rgbtRed * gy[r][c];
                        totalGy += image[curRow][curCol].rgbtGreen * gy[r][c];
                        totalBy += image[curRow][curCol].rgbtBlue * gy[r][c];
                    }
                }
            }
            finalR = round(sqrt(totalRx * totalRx + totalRy * totalRy));
            finalG = round(sqrt(totalGx * totalGx + totalGy * totalGy));
            finalB = round(sqrt(totalBx * totalBx + totalBy * totalBy));

            demo[row][col].rgbtRed = finalR > 255 ? 255 : finalR;
            demo[row][col].rgbtGreen = finalG > 255 ? 255 : finalG;
            demo[row][col].rgbtBlue = finalB > 255 ? 255 : finalB;
        }
    }

    //copy final image[][]
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = demo[i][j];
        }
    }

    return;
}
