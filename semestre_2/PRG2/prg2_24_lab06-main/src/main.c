/*
===============================================================================
File:                   main.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          03.04.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which the fleet must be created and
                        informations about the fleet must then be displayed in a
                        YAML or text format depending on config.h settings.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "config.h"
#include "ship.h"

int main(int argc, char *argv[])
{
    struct fleet fleet;
    int rc;

    fleet.nb_ships = 0;

    printf("Please select the number of ships for your fleet\n");

    // Check user input and reask for new one if not valid
    do
    {
        scanf("%d", &fleet.ship_capacity);
        while (getchar() != '\n')
            ;
        if (fleet.ship_capacity <= 0)
        {
            printf("Invalid input. Please enter a positive number.\n");
        }
    } while (fleet.ship_capacity <= 0);

    fleet.ships = malloc(fleet.ship_capacity * sizeof(struct ship));

    // Handle error and end execution if memory allocation fails
    if (fleet.ships == NULL)
    {
        printf("Memory allocation failed. Exiting program.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < fleet.ship_capacity; i++)
    {
        printf("Ship number %d:\n", i + 1);
        rc = addShipToFleet(&fleet);

        // Handle error, free memory and end execution if adding ship fails
        if (rc < 0)
        {
            printf("Error adding ship to fleet. Exiting program.\n");
            free(fleet.ships);
            return EXIT_FAILURE;
        }

        printf("\n");
    }

    for (int i = 0; i < fleet.nb_ships; i++)
    {
// Execute the following line ONLY if YAML is not set
#if YAML_FORMAT
        printf("- ");
#else
        printf("Ship number %d: \n", i + 1);

#endif
        displayShipInfos(&fleet.ships[i]);
    }

    // Free memory
    for (int i = 0; i < fleet.nb_ships; i++)
    {
        free(fleet.ships[i].name);
        free(fleet.ships[i].model);
    }
    free(fleet.ships);

    return EXIT_SUCCESS;
}
