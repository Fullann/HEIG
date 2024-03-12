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
Description:            In this file you should implement a simple programm 
                        in order to explore some basic pointers usage.
===============================================================================
*/

#include <stdlib.h>
#include <stdio.h>

#include <stdio.h>

int main() {
    // Création d'une variable de type int et assignation d'une valeur
    int variable = 3;

    // Création d'un pointeur sur int et assignation de l'adresse de la variable
    int *pointeur = &variable;

    // Affichage de l'adresse pointée par le pointeur
    printf("Adresse pointée par le pointeur : %p\n", (void *)pointeur);

    // Affichage de la valeur de la variable en déréférençant le pointeur
    printf("Valeur de la variable en déréférençant le pointeur : %d\n", *pointeur);

    // Modification de la variable de base
    variable = 33;

    // Affichage de la valeur de la variable en déréférençant le pointeur
    printf("Valeur de la variable en déréférençant le pointeur après modification : %d\n", *pointeur);

    // Modification de la valeur de la variable à travers le pointeur
    *pointeur = 126;

    // Affichage de la valeur de la variable de base
    printf("Valeur de la variable de base après modification à travers le pointeur : %d\n", variable);

    return 0;
}
