/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Battleship                             ______   _______      _______.      *
 * ship.c                                /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: BSD-3                                                      /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#include "ship.h"

Ship*
create_ship(void) {
    Ship* ship = malloc(sizeof(*ship));
    if (NULL == ship) {
        fprintf(stderr, "Error: malloc_ship: malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    ship->type = SHIP_NONE;
    ship->orientation = ORIENTATION_HORIZONTAL;

    return ship;
}

void
set_ship(Ship* ship, ShipType type, Orientation orientation) {
    ship->type = type;
    ship->orientation = orientation;
}

void
set_ship_type(Ship* ship, ShipType type) {
    ship->type = type;
}

void
set_ship_orientation(Ship* ship, Orientation orientation) {
    ship->orientation = orientation;
}

void
free_ship(Ship* ship) {
    if (NULL != ship) {
        free(ship);
    }
}

int
get_ship_size(ShipType type) {
    switch (type) {
        case SHIP_NONE:
            return 0;
        case SHIP_CARRIER:
            return SHIP_CARRIER_SIZE;
        case SHIP_FRIGATE:
            return SHIP_FRIGATE_SIZE;
        case SHIP_CRUISER:
            return SHIP_CRUISER_SIZE;
        case SHIP_DESTROYER:
            return SHIP_DESTROYER_SIZE;
        default:
            return 0;
    }
}
