/*
===============================================================================
File:                   bmp.h
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          25.04.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which the utils functions for the BMP
                        file format are declared, as well as the structures used.
===============================================================================
*/

#ifndef BMP_H
#define BMP_H

#include <stdint.h>

#pragma pack(push, 1)
typedef struct {
    uint16_t magic; // Nombre MAGIC
    uint32_t fileSize; // Taille totale du fichier
    uint16_t reserved1; // Réservé (0)
    uint16_t reserved2; // Réservé (0)
    uint32_t dataOffset; // Offset des données de l'image
    uint32_t headerSize; // Taille de l'en-tête du fichier
    int32_t width; // Largeur de l'image
    int32_t height; // Hauteur de l'image
    uint16_t planes; // Nombre de plans (toujours 1)
    uint16_t bpp; // Bits par pixel (24 bits dans notre cas)
    uint32_t compression; // Méthode de compression (0 pour non compressé)
    uint32_t imageSize; // Taille de l'image (sans en-tête)
    int32_t xResolution; // Résolution horizontale (en pixels par mètre)
    int32_t yResolution; // Résolution verticale (en pixels par mètre)
    uint32_t colorsUsed; // Nombre de couleurs utilisées dans l'image (0 pour toutes)
    uint32_t importantColors; // Nombre de couleurs importantes (0 pour toutes)
} BMPHeader;
#pragma pack(pop)

typedef struct {
    BMPHeader header;
    uint8_t* data;
} BMPImage;

BMPImage* read_bmp(const char* filename);
int write_bmp(const char* filename, BMPImage* image);
void free_bmp(BMPImage* image);

#endif // BMP_H

