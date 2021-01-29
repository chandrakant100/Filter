#include "helpers.h"
#include<math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    int avg;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // if the colours in each pixel are same then it skips the statement
            if ((image[i][j].rgbtRed == image[i][j].rgbtBlue) && (image[i][j].rgbtBlue == image[i][j].rgbtGreen)
                && (image[i][j].rgbtRed == image[i][j].rgbtGreen))
            {
                continue;
            }
            else
            {
                // other wise it calculates the average
                average = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0;

                avg = average;
                average = average - avg;
                //checks for the rounding value
                if (average == 0.5)
                {
                }
                else if (average > 0.5)
                {
                    avg ++;
                }
                // assign the values to the corresponding pixel grid
                image[i][j].rgbtRed = avg;
                image[i][j].rgbtBlue = avg;
                image[i][j].rgbtGreen = avg;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int num = height, num2 = width;

    // loop iterates in alternative direction
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // values from the image is stored in temp 2d array
            temp[i][j] = image[i][num2 - 1];
            num2 --;
        }
        num2 = width;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // reassign values to images from the temp 2d array
            image[i][j] = temp[i][j];
        }
    }
    return;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float count = 0;
    int red = 0, blue = 0, green = 0;

    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // values are assigned to a 2d array temp
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red = 0;
            blue = 0;
            green = 0;
            count = 0.0;

            for (int a = i - 1; a <= i + 1; a++)
            {
                // check for values which are not in the grid
                if (a < 0)
                {
                    continue;
                }
                else if (a > (height - 1))
                {
                    break;
                }
                for (int b = j - 1; b <= j + 1; b++)
                {
                    if (b < 0)
                    {
                        continue;
                    }
                    else if (b > (width - 1))
                    {
                        break;
                    }
                    // assign the values by calculating the average
                    red += temp[a][b].rgbtRed;
                    blue += temp[a][b].rgbtBlue;
                    green += temp[a][b].rgbtGreen;
                    count ++;
                }
            }
            // reassign the values to the image by rounding the sum of colous of each pixel
            image[i][j].rgbtRed = round(red / count);
            image[i][j].rgbtBlue = round(blue / count);
            image[i][j].rgbtGreen = round(green / count);
        }
    }
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    // creates gx and gy grid for edge detectation
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    float gxRCount = 0.0, gyRCount = 0.0;
    float gxBCount = 0.0, gyBCount = 0.0;
    float gxGCount = 0.0, gyGCount = 0.0;

    // assign the counter variables to 0
    int k = 0, l = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // stores the values of pixel to a temp 2d array
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gxRCount = 0.0, gyRCount = 0.0;
            gxBCount = 0.0, gyBCount = 0.0;
            gxGCount = 0.0, gyGCount = 0.0;

            // reassign the counter variable to zero
            k = 0;
            l = 0;
            for (int a = i - 1; a <= i + 1; a++)
            {
                l = 0;
                for (int b = j - 1; b <= j + 1; b++)
                {
                    if ((a < 0 || a > (height - 1)) || (b < 0 || b > (width - 1)))
                    {
                        // if the colour is out of the grid then assign to the sum
                        gxRCount += gx[k][l] * 0.0;
                        gyRCount += gx[k][l] * 0.0;
                        gxBCount += gx[k][l] * 0.0;
                        gyBCount += gx[k][l] * 0.0;
                        gxGCount += gx[k][l] * 0.0;
                        gyGCount += gx[k][l] * 0.0;
                    }
                    else
                    {
                        // else assign the colour values of each pixel corresponding to the gx and gy grid by multiplying with gx and gy
                        gxRCount += gx[k][l] * temp[a][b].rgbtRed;
                        gyRCount += gy[k][l] * temp[a][b].rgbtRed;
                        gxBCount += gx[k][l] * temp[a][b].rgbtBlue;
                        gyBCount += gy[k][l] * temp[a][b].rgbtBlue;
                        gxGCount += gx[k][l] * temp[a][b].rgbtGreen;
                        gyGCount += gy[k][l] * temp[a][b].rgbtGreen;
                    }
                    l += 1;
                }
                k += 1;
            }
            // if staement checks for the values greater then 255 after rounding each indivisual sum corresponding to each pixel colour
            if (round(sqrt((gxRCount * gxRCount) + (gyRCount * gyRCount))) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(sqrt((gxRCount * gxRCount) + (gyRCount * gyRCount)));
            }
            if (round(sqrt((gxBCount * gxBCount) + (gyBCount * gyBCount))) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(sqrt((gxBCount * gxBCount) + (gyBCount * gyBCount)));
            }
            if (round(sqrt((gxGCount * gxGCount) + (gyGCount * gyGCount))) > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(sqrt((gxGCount * gxGCount) + (gyGCount * gyGCount)));
            }
        }
        return;
    }
}