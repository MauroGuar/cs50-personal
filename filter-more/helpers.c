#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            const RGBTRIPLE pixel = image[i][j];
            const int color_average = (int) round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3.0);
            image[i][j].rgbtRed = color_average;
            image[i][j].rgbtGreen = color_average;
            image[i][j].rgbtBlue = color_average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width / 2; ++j) {
            const RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int channels_sum[] = {0, 0, 0};
            short pixel_count = 0;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    int row_neightbour = i + di;
                    int column_neightbour = j + dj;
                    if (row_neightbour >= 0 && row_neightbour < height && column_neightbour >= 0 && column_neightbour <
                        width) {
                        channels_sum[0] += image[row_neightbour][column_neightbour].rgbtRed;
                        channels_sum[1] += image[row_neightbour][column_neightbour].rgbtGreen;
                        channels_sum[2] += image[row_neightbour][column_neightbour].rgbtBlue;
                        pixel_count++;
                    }
                }
            }
            image_copy[i][j].rgbtRed = (int) round(channels_sum[0] / (float) pixel_count);
            image_copy[i][j].rgbtGreen = (int) round(channels_sum[1] / (float) pixel_count);
            image_copy[i][j].rgbtBlue = (int) round(channels_sum[2] / (float) pixel_count);
        }
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            image[i][j] = image_copy[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
    return;
}
