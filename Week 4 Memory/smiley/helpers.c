#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int row = 0; row < width; row++)
    {
        for (int column = 0; column < height; column++)
        {
            if (image[column][row].rgbtBlue == 0 && image[column][row].rgbtGreen == 0 && image[column][row].rgbtRed == 0)
            {
                image[column][row].rgbtBlue = 0;
                image[column][row].rgbtGreen = 255;
                image[column][row].rgbtRed = 255;
            }
        }
    }
}
