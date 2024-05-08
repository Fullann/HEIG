/*
===============================================================================
File:                   command_ship.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          03.04.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which functions specific to command
                        ships must be implemented
===============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command_ship.h"

void addCommandShipDetails(struct command_ship *command_ship)
{
    command_ship->commander_name = (char *)malloc(100 * sizeof(char));

    printf("Please enter the commander's name!\n");
    scanf("%s", command_ship->commander_name);

    printf("Please enter the number of passengers in the ship!\n");
    scanf("%d", &command_ship->nb_passengers);
}

#if YAML_FORMAT
void displayCommandShipDetails(const struct command_ship *command_ship)
{
    printf("  type: Command\n");
    printf("  commander_name: %s\n", command_ship->commander_name);
    printf("  nb_passengers: %d\n", command_ship->nb_passengers);
}
#else
void displayCommandShipDetails(const struct command_ship *command_ship)
{
    printf("Ship type: Command\n");
    printf("Commander's name: %s\n", command_ship->commander_name);
    printf("Number of passengers: %d\n", command_ship->nb_passengers);
}
#endif

