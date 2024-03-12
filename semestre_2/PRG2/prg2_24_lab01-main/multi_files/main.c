/*
===============================================================================
File:                   main.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          21.11.2023
Modification Author:    
Modification Date:
Version:                1.0
Description:            This is a simple Hello World file which is calling a
                        function from a custom library.
===============================================================================
*/


#include <stdio.h>
#include <stdlib.h>

#include "a_simple_lib.h"

int main(int argc, char** argv){
    printf("Hello World!\n");
    print_hello_world();
}
