/*
===============================================================================
File:                   problems.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          07.12.2023
Modification Author:
Modification Date:
Version:                1.0
Description:            In this file, some prints are made but the result are not
                        what we expect, maybe some corrections would fix it!
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    // DO NOT MODIFY
    int i = 0;
    unsigned int u = 0;
    double d = 0.0;
    char c = 0;

    // DO NOT MODIFY
    i = 10;
    d = 3.0;

    // Example 1 - Modifie this line for a result of 3
    printf("Exemple 1 : %d / %.2f = %.0f\n", i, d, (double)i / d);

    // DO NOT MODIFY
    i = 0xFFFFFFFF;

    // Example 2 - Modifie this line for a result of 255
    printf("Exemple 2 : %u\n", (unsigned int)(i & 0xFF));

    // Example 3 - Modifie this line for a result of 4294967295
    printf("Exemple 3 : %u\n", (unsigned int)i); // Cast i en unsigned int

    // DO NOT MODIFY
    c = 'B';

    // Example 4 - Modifie this line for a result of 66
    printf("Exemple 4 : %d\n", (int)c); // Cast c en int

    // DO NOT MODIFY
    i = 1;
    c = 3;
    d = 100;

    // Example 5 - Modifie this line for a result of 33
    printf("Exemple 5 : %d / %d * %.2f = %d\n", i, c, d, (int)(i / (float)c * d));

    // DO NOT MODIFY
    u = 0xFFFFFFFF;

    // Example 6 - Modifie this line for a result of 0xFFFFFFFF
     printf("Exemple 6 : 0x%X * 2 / 2 = 0x%X\n", u, (unsigned int)(((unsigned long long)u) * 2 / 2));

    return EXIT_SUCCESS;
}