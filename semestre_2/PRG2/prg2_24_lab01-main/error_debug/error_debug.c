/*
===============================================================================
File:                   error_debug.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          22.11.2023
Modification Author:    
Modification Date:
Version:                1.0
Description:            This is a simple programm, but some instructions are 
                        causing execution error, this should be fixed by debugging
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>

// Function to display a welcome message 
void printWelcomeMessage() {
    printf("Welcome to this debugg exercice!\n");
}

// Function to compute the sum of the integers from 1 to n
int calculateSum(int n) {
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += i;
    }
    return sum;
}

// Function that does some simple operations on a variable and a pointer
void pointersGame(void) {
    int value = 0;
    int *pointer = NULL;

    pointer = &value;

    value++;

    (*pointer)++;

    *pointer = 55;

    pointer = NULL;

    value = *pointer;

    value *= 10;

    pointer = NULL;
}

// Main function
int main() {
    // some variables declarations
    int Value = 10;
    int result;
    int a = 10;
    int b = 0;

    // Display the welcome message
    printWelcomeMessage();
    
    // Computes the summ of integers from 1 to Value
    result = calculateSum(Value);

    // DO NOT COMMENT THIS LINE
    pointersGame();

    // Display the result of the computing
    printf("The summ of integers from 1 to %d is : %d\n", Value, result);

    // Making another calculus
    result = a / b;

    printf("This is the end, everything went fine! \\o/\n");

    return 0;
}
