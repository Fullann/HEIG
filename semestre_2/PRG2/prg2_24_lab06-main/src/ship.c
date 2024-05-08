/*
===============================================================================
File:                   ship.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          03.04.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which all common ships functions must
                        be implemented.
===============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include "ship.h"
#include "combat_ship.h"
#include "cargo_ship.h"
#include "command_ship.h"

int addShipToFleet(struct fleet *fleet)
{
    if (fleet->nb_ships >= fleet->ship_capacity)
    {
        printf("The fleet is already at maximum capacity.\n");
        return -1;
    }

    struct ship *new_ship = &fleet->ships[fleet->nb_ships];

    new_ship->name = (char *)malloc(100 * sizeof(char));
    new_ship->model = (char *)malloc(100 * sizeof(char));

    printf("Please enter a name for your ship!\n");
    scanf("%s", new_ship->name);
    printf("Please enter a model for your ship!\n");
    scanf("%s", new_ship->model);

    int ship_type;
    printf("Please choose the ship type:\n");
    printf("1: Combat ship\n");
    printf("2: Cargo ship\n");
    printf("3: Command ship\n");
    scanf("%d", &ship_type);

    switch (ship_type)
    {
    case 1:
        new_ship->type = COMBAT;
        addCombatShipDetails(&new_ship->details.combat);
        break;
    case 2:
        new_ship->type = CARGO;
        addCargoShipDetails(&new_ship->details.cargo);
        break;
    case 3:
        new_ship->type = COMMAND;
        addCommandShipDetails(&new_ship->details.command);
        break;
    default:
        printf("Invalid ship type.\n");
        return -1;
    }

    fleet->nb_ships++;
    return 0;
}

void displayShipInfos(const struct ship *ship)
{
#if YAML_FORMAT
    printf("name: %s\n", ship->name);
printf("  model: %s\n", ship->model);
#else
    printf("Ship name: %s\n", ship->name);
    printf("Ship model: %s\n", ship->model);
#endif


    switch (ship->type)
    {
    case COMBAT:
        displayCombatShipDetails(&ship->details.combat);
        break;
    case CARGO:
        displayCargoShipDetails(&ship->details.cargo);
        break;
    case COMMAND:
        displayCommandShipDetails(&ship->details.command);
        break;
    default:
        printf("Unknown ship type.\n");
    }
}
