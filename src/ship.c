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
    ship->head = malloc(sizeof(*ship->head) * COORDINATE_SIZE);
    if (NULL == ship->head) {
        fprintf(stderr, "Error: malloc_ship: malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    ship->head[0] = 0;
    ship->head[1] = 0;

    return ship;
}

int*
calculate_tail(Ship* ship) {
    int* tail = malloc(sizeof(*tail) * COORDINATE_SIZE);
    if (NULL == tail) {
        fprintf(stderr, "Error: malloc_ship: malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    tail[0] = ship->head[0];
    tail[1] = ship->head[1];
    switch (ship->orientation) {
        case ORIENTATION_HORIZONTAL:
            tail[0] += get_ship_size(ship->type) - 1;
            break;
        case ORIENTATION_VERTICAL:
            tail[1] += get_ship_size(ship->type) - 1;
            break;
    }
    return tail;
}

void
set_ship(Ship* ship, ShipType type, Orientation orientation, int x, int y) {
    ship->type = type;
    ship->orientation = orientation;
    ship->head[0] = x;
    ship->head[1] = y;
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
        if (NULL != ship->head) {
            free(ship->head);
        }
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
