/*
===============================================================================
File:                   gray.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          25.04.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which the program to convert a BMP
                        image to black and white is implemented.
===============================================================================
*/
#include "bmp.h"
#include <stdio.h>

void convert_to_grayscale(BMPImage* image) {
    for (uint32_t i = 0; i < image->header.imageSize; i += 3) {
        uint8_t blue = image->data[i];
        uint8_t green = image->data[i + 1];
        uint8_t red = image->data[i + 2];
        uint8_t gray = (red + green + blue) / 3;
        image->data[i] = gray;
        image->data[i + 1] = gray;
        image->data[i + 2] = gray;
    }
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

    convert_to_grayscale(input_image);

    if (!write_bmp(argv[2], input_image)) {
        fprintf(stderr, "Error writing output image\n");
        free_bmp(input_image);
        return 1;
    }

    printf("Images is gray\n");

    free_bmp(input_image);
    return 0;
}
