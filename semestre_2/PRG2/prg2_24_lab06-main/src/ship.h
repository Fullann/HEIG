/*
===============================================================================
File:                   ship.h
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          03.04.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which all common ships functions must
                        be declared. The The struct / enum for the common part of
                        all the ship's datas must also be declared here.
===============================================================================
*/
#ifndef SHIP_H
#define SHIP_H

#include "combat_ship.h"
#include "cargo_ship.h"
#include "command_ship.h"

enum ShipType
{
    COMBAT,
    CARGO,
    COMMAND
};

struct ship
{
    char *name;
    char *model;
    enum ShipType type;
    union
    {
        struct cargo_ship cargo;
        struct combat_ship combat;
        struct command_ship command;
    } details;
};

struct fleet
{
    struct ship *ships;
    int nb_ships;
    int ship_capacity;
};

int addShipToFleet(struct fleet *fleet);
void displayShipInfos(const struct ship *ship);

#endif /* SHIP_H */
