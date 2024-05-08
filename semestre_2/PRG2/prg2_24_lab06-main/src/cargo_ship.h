/*
===============================================================================
File:                   cargo_ship.h
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          03.04.2024
Modification Author:
Modification Date:
Version:                1.0
Description:            This is the file in which functions specific to cargo
                        ships must be declared. The struct for cargo ships
                        specific datas must also be declared here.
===============================================================================
*/
#ifndef CARGO_SHIP_H
#define CARGO_SHIP_H

struct cargo_ship
{
    int max_cargo_weight;
};

void addCargoShipDetails(struct cargo_ship *cargo_ship);
void displayCargoShipDetails(const struct cargo_ship *cargo_ship);

#endif /* CARGO_SHIP_H */
