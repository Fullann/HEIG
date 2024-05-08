/*
===============================================================================
File:                   command_ship.h
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          03.04.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which functions specific to command
                        ships must be declared. The struct for command ships
                        specific datas must also be declared here.
===============================================================================
*/
#ifndef COMMAND_SHIP_H
#define COMMAND_SHIP_H

struct command_ship
{
    char *commander_name;
    int nb_passengers;
};

void addCommandShipDetails(struct command_ship *command_ship);
void displayCommandShipDetails(const struct command_ship *command_ship);

#endif /* COMMAND_SHIP_H */
