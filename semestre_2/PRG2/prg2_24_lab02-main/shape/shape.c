/*
===============================================================================
File:                   shape.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          07.12.2023
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which exercice 1 must be implemented
                        User should be able to select a shape to display and it's size
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

void displaySquare(int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void displayTriangle(int size) {
    int i = 0;
    do {
        int j = 0;
        do {
            printf("*");
            j++;
        }
        while (j <= i);
        printf("\n");
        i++;
    }
    while (i < size);
}

void displayReverseTriangle(int size) {
    int i = size;
    while (i > 0) {
        int j = size - i;
        while (j > 0) {
            printf(" ");
            j--;
        }
        j = i;
        while (j > 0) {
            printf("*");
            j--;
        }
        printf("\n");
        i--;
    }
}

void displayDiamond(int size) {
    // Upper part of the diamond
    int spaces = size / 2;
    int stars = 1;

    for (int i = 0; i < size / 2 + 1; i++) {
        for (int j = 0; j < spaces; j++) {
            printf(" ");
        }

        for (int j = 0; j < stars; j++) {
            printf("*");
        }

        printf("\n");
        spaces--;
        stars += 2;
    }

    // Lower part of the diamond
    spaces = 1;
    stars = size - 2;

    for (int i = 0; i < size / 2; i++) {
        for (int j = 0; j < spaces; j++) {
            printf(" ");
        }

        for (int j = 0; j < stars; j++) {
            printf("*");
        }

        printf("\n");
        spaces++;
        stars -= 2;
    }
}

void viderBuffer() {
    int c = 0;
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

int main() {
    int choice;
    int size;

    printf("Welcome to the PRG2-24 shape generator!\n\n");
    printf("Please select one of the following shapes to display:\n");
    printf("1: Square\n2: Triangle\n3: Reverse triangle\n4: Diamond\n");

    // Demander à l'utilisateur de saisir la form
    printf("Enter your choice (1-4): ");

    while (1) {
        if (scanf("%d", &choice) != 1 && choice < 1 || choice > 4) {
            printf("Invalid shape! Please select a number between 1 and 4\n");
        } else {
            break;
        }
        viderBuffer();
    }

    // Demander à l'utilisateur de saisir la taille
    printf("\nNow select a size for your shape: ");
    while (1) {
        if (scanf("%d", &size) != 1 && size < 1 || size > 20 || (choice == 4 && size % 2 == 0)) {
            printf("Invalid size! Please select a valid value\n");
        } else {
            break;
        }
        viderBuffer();
    }

    // Afficher la forme sélectionnée avec la taille choisie
    printf("\n");

    switch (choice) {
    case 1:
        displaySquare(size);
        break;
    case 2:
        displayTriangle(size);
        break;
    case 3:
        displayReverseTriangle(size);
        break;
    case 4:
        displayDiamond(size);
        break;
    }

    return 0;
}
