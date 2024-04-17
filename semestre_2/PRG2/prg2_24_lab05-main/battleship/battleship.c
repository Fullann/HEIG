/*
===============================================================================
File:                   battleship.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          05.03.2024
Modification Author:    
Modification Date:
Version:                1.0
Description:            This is the file in which exercice 1 must be implemented
                        User should be able to play a simplified battleship game
                        using only 1 32bits variable to store all the game datas
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE  12

int main(int argc, char *argv[]) {
    // Create your variables here
    const int ennemy = 1;
    int user;
    
    //0->11 = position des bateaux
    //12->23 = position des attaques
    //24->27 = nombre de vie
    //28->31 = nombre de bateau restant
    unsigned game = 0x00000000;
    int nb_ship = 0x60000000;
    int lifes = 0x06000000;


    //set ship and lifes
    game |= nb_ship;
    game |= lifes;

    // initialize rand here
    srand(time(NULL));

    //generate 6 ennemies | Ennemy = 1
    for (size_t i = 0; i < ((game >> 28) & 0xF); ++i) {
        int rnd = rand() % BOARD_SIZE;

        //check if case is already use
        while (((game >> rnd) & 1) == ennemy) {
            rnd = rand() % BOARD_SIZE;
        }

        int mask = 1 << rnd;
        game |= mask;
    }

    while (1) {
        unsigned temp_ship = (game >> 28) & 0xF;
        unsigned temp_life = (game >> 24) & 0x0F;

        printf("%d lifes remaining, %d ships remaining\n", temp_life, temp_ship);

        while (1) {
            printf("Please select a position to attack between 0 and 11!\n");
            if (scanf("%d", &user) == 1) {
                break;
            }

            //Vider buffer
            int c = 0;
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
        }

        if (((game >> (12 + user)) & 0x1) == 1){
            printf("Already attacked this position\n");
        } else if (((game >> user) & 0x1) == 0){
            --temp_life;

            //save new nb life
            game &= 0xF0FFFFFF;
            game |= (temp_life << 24);

            //save attack
            game |= (0x1 << (12 + user));

            printf("MISS\n");

        } else if (((game >> user) & 0x1) == 1){
            --temp_ship;

            //save new nb ship
            game &= 0x0FFFFFFF;
            game |= (temp_ship << 28);

            //save attack
            game |= (0x1 << (12 + user));

            printf("HIT\n");
        }

        if (temp_life == 0 || temp_ship == 0) {
            break;
        }
    }

    if (((game >> 24) & 0x0F) == 0) {
        printf("YOU LOOSE\n");
    } else if (((game >> 28) & 0xF) == 0) {
        printf("YOU WIN\n");
    }

    return EXIT_SUCCESS;
}