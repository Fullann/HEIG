/*
===============================================================================
File:                   battleship.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          15.01.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which exercice 1 must be implemented
                        User should be able to play a simplified battleship game
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE  10

int main(int argc, char *argv[]) {
    // Create your variables here
    const int void_case = 0;
    const int ennemy = 1;
    const int use = 2;
    int lifes = 5;
    int nb_ship = 3;
    int user;
    int board[BOARD_SIZE];

    //Generate void case | vide = 0
    for (size_t i = 0; i < BOARD_SIZE; ++i) {
        board[i] = void_case;
    }

    // initialize rand here
    srand(time(NULL));

    //generate 3 ennemies | Ennemy = 1
    for (size_t i = 0; i < nb_ship;++i) {
        int rnd = rand() % BOARD_SIZE;

        //check if case is already use
        while (board[rnd] == ennemy) {
            rnd = rand() % BOARD_SIZE;
        }

        board[rnd] = ennemy;
    }

    // TO BE IMPLEMENTED
    while (1) {
        printf("%d lifes remaining, %d ships remaining\n", lifes, nb_ship);

        while (1) {
            printf("Please select a position to attack between 0 and 9!\n");
            if (scanf("%d", &user) == 1) {
                break;
            }

            //Vider buffer
            int c = 0;
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
        }

        switch (board[user]) {
        case 0:
            --lifes;
            board[user] = use;
            printf("MISS\n");
            break;
        case 1:
            --nb_ship;
            board[user] = use;
            printf("HIT\n");
            break;
        case 2:
            printf("Already attacked this position\n");
            break;
        }

        if (lifes == 0 || nb_ship == 0) {
            break;
        }
    }

    if (lifes == 0) {
        printf("YOU LOOSE\n");
    } else if (nb_ship == 0) {
        printf("YOU WIN\n");
    }

    return EXIT_SUCCESS;
}
