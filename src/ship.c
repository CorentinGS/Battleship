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

/*
 * This function is used to create a new ship.
 * @return a pointer to the new ship.
 */
Ship*
create_ship(void) {
    /* Allocate memory for the ship */
    Ship* ship = malloc(sizeof(*ship));
    if (NULL == ship) {
        fprintf(stderr, "Error: malloc_ship: malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    /* Initialize the ship */
    ship->type = SHIP_NONE;
    ship->orientation = ORIENTATION_HORIZONTAL;
    /* Allocate memory for the ship head */
    ship->head = malloc(sizeof(*ship->head) * COORDINATE_SIZE);
    if (NULL == ship->head) {
        fprintf(stderr, "Error: malloc_ship: malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    /* Initialize the ship head */
    ship->head[0] = 0;
    ship->head[1] = 0;

    /* Return the ship */
    return ship;
}

/*
 * This function is used to set a ship.
 * @param ship the ship to set.
 * @param type the type of the ship.
 * @param orientation the orientation of the ship.
 * @param x the x coordinate of the ship head.
 * @param y the y coordinate of the ship head.
 */
void
set_ship(Ship* ship, ShipType type, Orientation orientation, int x, int y) {
    ship->type = type;
    ship->orientation = orientation;
    ship->head[0] = x;
    ship->head[1] = y;
}

/*
 * This function is used to free a ship.
 * @param ship the ship to free.
 */
void
free_ship(Ship* ship) {
    if (NULL != ship) {
        /* Free the ship head */
        if (NULL != ship->head) {
            free(ship->head);
        }
        free(ship);
    }
}

/*
 * This function is used to get the size of a ship.
 * @param type the type of the ship.
 * @return the size of the ship.
 */
int
get_ship_size(ShipType type) {
    switch (type) {
        case SHIP_CARRIER:
            return SHIP_CARRIER_SIZE;
        case SHIP_FRIGATE:
            return SHIP_FRIGATE_SIZE;
        case SHIP_CRUISER:
            return SHIP_CRUISER_SIZE;
        case SHIP_DESTROYER:
            return SHIP_DESTROYER_SIZE;
        case SHIP_NONE:
        default:
            return 0;
    }
}
