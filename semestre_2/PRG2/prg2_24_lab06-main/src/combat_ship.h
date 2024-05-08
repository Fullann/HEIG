/*
===============================================================================
File:                   combat_ship.h
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          03.04.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which functions specific to combat
                        ships must be declared. The struct for combat ships
                        specific datas must also be declared here.
===============================================================================
*/
#ifndef COMBAT_SHIP_H
#define COMBAT_SHIP_H

struct combat_ship
{
    char *pilot_name;
    char droid_serie[10];
};

void addCombatShipDetails(struct combat_ship *combat_ship);
void displayCombatShipDetails(const struct combat_ship *combat_ship);

#endif /* COMBAT_SHIP_H */
