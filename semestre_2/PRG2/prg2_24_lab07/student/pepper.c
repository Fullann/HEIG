/*
===============================================================================
File:                   pepper.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          25.04.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which the program to remove salt-and-pepper
                        noise from a BMP image is implemented.
===============================================================================
*/
#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>

void bubble_sort(uint8_t* array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                uint8_t temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void apply_median_filter(BMPImage* image) {
    int width = image->header.width;
    int height = image->header.height;
    int row_size = (width * 3 + 3) & ~3; // Row size must be multiple of 4 bytes
    uint8_t* filtered_data = malloc(image->header.imageSize);

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            uint8_t neighbors[9];
            int index = 0;
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    int pos = (y + j) * row_size + (x + i) * 3;
                    neighbors[index++] = image->data[pos];
                }
            }

            bubble_sort(neighbors, 9);
            uint8_t median = neighbors[4];

            int pos = y * row_size + x * 3;
            filtered_data[pos] = median;
            filtered_data[pos + 1] = median;
            filtered_data[pos + 2] = median;
        }
    }

    // Copy border pixels
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1) {
                int pos = y * row_size + x * 3;
                filtered_data[pos] = image->data[pos];
                filtered_data[pos + 1] = image->data[pos + 1];
                filtered_data[pos + 2] = image->data[pos + 2];
            }
        }
    }

    free(image->data);
    image->data = filtered_data;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input bmp> <output bmp>\n", argv[0]);
        return 1;
    }

    BMPImage* input_image = read_bmp(argv[1]);
    if (!input_image) {
        fprintf(stderr, "Error reading input image\n");
        return 1;
    }

    apply_median_filter(input_image);

    if (!write_bmp(argv[2], input_image)) {
        fprintf(stderr, "Error writing output image\n");
        free_bmp(input_image);
        return 1;
    }

    printf("Images is clear\n");

    free_bmp(input_image);
    return 0;
}
