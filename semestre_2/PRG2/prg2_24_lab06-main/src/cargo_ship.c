/*
===============================================================================
File:                   cargo_ship.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          03.04.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which functions specific to cargo
                        ships must be implemented
===============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cargo_ship.h"

void addCargoShipDetails(struct cargo_ship *cargo_ship)
{
    printf("Please enter the maximum cargo's weight that the ship can transport!\n");
    scanf("%d", &cargo_ship->max_cargo_weight);
}

#if YAML_FORMAT
void displayCargoShipDetails(const struct cargo_ship *cargo_ship)
{
    printf("  type: Cargo\n");
    printf("  max_cargo_weight: %d\n", cargo_ship->max_cargo_weight);
}
#else
void displayCargoShipDetails(const struct cargo_ship *cargo_ship)
{
    printf("Ship type: Cargo\n");
    printf("Max cargo weight [kg]: %d\n", cargo_ship->max_cargo_weight);
}
#endif

