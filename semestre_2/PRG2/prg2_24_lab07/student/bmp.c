/*
===============================================================================
File:                   bmp.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          25.04.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which the utils functions for the BMP
                        file format are implemented.
===============================================================================
*/
#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>

BMPImage* read_bmp(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) return NULL;

    BMPImage* image = malloc(sizeof(BMPImage));
    if (!image) {
        fclose(file);
        return NULL;
    }

    fread(&image->header, sizeof(BMPHeader), 1, file);
    if (image->header.magic != 0x4D42) {
        fclose(file);
        free(image);
        return NULL;
    }

    image->data = malloc(image->header.imageSize);
    if (!image->data) {
        fclose(file);
        free(image);
        return NULL;
    }

    fseek(file, image->header.dataOffset, SEEK_SET);
    fread(image->data, image->header.imageSize, 1, file);
    fclose(file);

    return image;
}

int write_bmp(const char* filename, BMPImage* image) {
    FILE* file = fopen(filename, "wb");
    if (!file) return 0;

    fwrite(&image->header, sizeof(BMPHeader), 1, file);
    fseek(file, image->header.dataOffset, SEEK_SET);
    fwrite(image->data, image->header.imageSize, 1, file);
    fclose(file);

    return 1;
}

void free_bmp(BMPImage* image) {
    if (image) {
        if (image->data) free(image->data);
        free(image);
    }
}
