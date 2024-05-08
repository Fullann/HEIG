/*
===============================================================================
File:                   combat_ship.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          03.04.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which functions specific to combat
                        ships must be implemented
===============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combat_ship.h"

void addCombatShipDetails(struct combat_ship *combat_ship)
{
    combat_ship->pilot_name = (char *)malloc(100 * sizeof(char));

    printf("Please enter the pilot's name!\n");
    scanf("%s", combat_ship->pilot_name);

    printf("Please choose an astromech serie from the following list: R1 R2 R3 BB\n");
    printf("Example: R2\n");
    scanf("%s", combat_ship->droid_serie);
}

#if YAML_FORMAT
void displayCombatShipDetails(const struct combat_ship *combat_ship)
{
    printf("  type: Combat\n");
    printf("  pilot_name: %s\n", combat_ship->pilot_name);
    printf("  droid_serie: %s series\n", combat_ship->droid_serie);
}
#else
void displayCombatShipDetails(const struct combat_ship *combat_ship)
{
    printf("Ship type: Combat\n");
    printf("Pilot's name: %s\n", combat_ship->pilot_name);
    printf("Droid serie: %s series\n", combat_ship->droid_serie);
}
#endif

