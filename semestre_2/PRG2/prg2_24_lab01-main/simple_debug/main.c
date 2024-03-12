/*
===============================================================================
File:                   main.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          22.11.2023
Modification Author:    
Modification Date:
Version:                1.0
Description:            This programm computes the summ of the integers from
                        1 to n (n value is hardcoded)
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int n = 10; // Hardcoding the value of N for this example

    int summ = 0;

    // Calcule la somme des entiers de 1 à n
    for (int i = 1; i <= n; ++i) {
        summ += i;
    }

    // Displays the result
    printf("The summ of integers from 1 to %d is : %d\n", n, summ);

    return 0;
}