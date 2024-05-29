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
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include <string.h>

int compare_images(const char* input_path, const char* ref_path, const char* output_path) {
    BMPImage* input_image = read_bmp(input_path);
    if (!input_image) {
        fprintf(stderr, "Error reading input image\n");
        return 0;
    }

    BMPImage* ref_image = read_bmp(ref_path);
    if (!ref_image) {
        fprintf(stderr, "Error reading reference image\n");
        free_bmp(input_image);
        return 0;
    }

    if (input_image->header.width != ref_image->header.width || input_image->header.height != ref_image->header.height) {
        fprintf(stderr, "Images have different dimensions\n");
        free_bmp(input_image);
        free_bmp(ref_image);
        return 0;
    }

    BMPImage* output_image = malloc(sizeof(BMPImage));
    if (!output_image) {
        fprintf(stderr, "Memory allocation error\n");
        free_bmp(input_image);
        free_bmp(ref_image);
        return 0;
    }
    memcpy(&output_image->header, &input_image->header, sizeof(BMPHeader));
    output_image->data = malloc(input_image->header.imageSize);
    if (!output_image->data) {
        fprintf(stderr, "Memory allocation error\n");
        free_bmp(input_image);
        free_bmp(ref_image);
        free(output_image);
        return 0;
    }

    int different = 0;
    for (uint32_t i = 0; i < input_image->header.imageSize; i += 3) {
        if (input_image->data[i] != ref_image->data[i] ||
            input_image->data[i+1] != ref_image->data[i+1] ||
            input_image->data[i+2] != ref_image->data[i+2]) {
            output_image->data[i] = 0;
            output_image->data[i+1] = 0;
            output_image->data[i+2] = 255;
            different = 1;
        } else {
            output_image->data[i] = input_image->data[i];
            output_image->data[i+1] = input_image->data[i+1];
            output_image->data[i+2] = input_image->data[i+2];
        }
    }

    if (!write_bmp(output_path, output_image)) {
        fprintf(stderr, "Error writing output image\n");
        free_bmp(input_image);
        free_bmp(ref_image);
        free_bmp(output_image);
        return 0;
    }

    free_bmp(input_image);
    free_bmp(ref_image);
    free_bmp(output_image);

    if (different) {
        printf("Images are different\n");
    } else {
        printf("Images are identical\n");
    }

    return 1;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input bmp> <reference bmp> <output bmp>\n", argv[0]);
        return 1;
    }

    if (!compare_images(argv[1], argv[2], argv[3])) {
        return 1;
    }

    return 0;
}

