/*
===============================================================================
File:                   exploration_sol.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          15.01.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            In this file you should iterate on an array without using
                        direct index.
===============================================================================
*/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int array[10] = {};

    for (size_t i = 0; i < 10; i++) {
        printf("%d", *(array + i));
    }

    for (size_t i = 0; i < 10; i++) {
        *(array + i) = i;
    }
    printf("\n");
    for (size_t i = 0; i < 10; i++) {
        printf("%d", *(array + i));
    }

}
