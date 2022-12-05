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
#include "board.h"

static int get_unique_ship_id(void);

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

    ship->id = get_unique_ship_id();

    /* Return the ship */
    return ship;
}

static int
get_unique_ship_id(void) {
    static int id = 0;
    return id++;
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

/*
 * This function is used to check if a ship is destroyed or not.
 * @param ship the ship to check.
 * @param board the board where the ship is.
 * @return TRUE if the ship is destroyed, FALSE otherwise.
 */
int
is_ship_destroyed(Ship* ship, Board* board) {
    int i, x, y, size;
    size = get_ship_size(ship->type);
    x = ship->head[0];
    y = ship->head[1];
    for (i = 0; i < size; i++) {
        if (ship->orientation == ORIENTATION_HORIZONTAL) {
            if (board->tiles[x + i][y].state == TILE_STATE_SHIP) {
                return FALSE;
            }
        } else {
            if (board->tiles[x][y + i].state == TILE_STATE_SHIP) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

/*
 * This function is used to hit a ship.
 * If the ship is destroyed, it will be marked as destroyed and removed from the board.
 * @param board the board where the ship is.
 * @param x the x coordinate of the tile to hit.
 * @param y the y coordinate of the tile to hit.
 * @return OK if the ship is hit/destroyed and an ERROR otherwise.
 */
int
hit_ship(Board* board, int x, int y) {
    Tile* tile;
    int error;
    Ship* ship;
    error = is_in_bounds(board, x, y);
    if (ERROR_TILE_OUT_OF_BOUNDS == error) {
        return ERROR_TILE_OUT_OF_BOUNDS;
    }
    tile = &board->tiles[x][y];

    switch (tile->state) {
        case TILE_STATE_SHIP:
            ship = get_ship_at(board, x, y);
            if (NULL == ship) {
                return ERROR;
            }
            tile->state = TILE_STATE_HIT;
            if (is_ship_destroyed(ship, board)) {
                remove_ship(board, ship);
            }

            return OK;
        case TILE_STATE_HIT:
            return INFO_TILE_ALREADY_HIT;
        default:
            return ERROR_TILE_NOT_SHIP;
    }
}

/*
 * This function is used to remove a ship from the board.
 * @param board the board where the ship is.
 * @param ship the ship to remove.
 * @return OK if the ship is removed and an ERROR otherwise.
 */
int
remove_ship(Board* board, Ship* ship) {
    int i;
    int size = get_ship_size(ship->type);
    int x = ship->head[0];
    int y = ship->head[1];
    for (i = 0; i < size; ++i) {
        if (ORIENTATION_HORIZONTAL == ship->orientation) {
            board->tiles[x + i][y].state = TILE_STATE_EMPTY;
        } else {
            board->tiles[x][y + i].state = TILE_STATE_EMPTY;
        }
    }

    free_ship(ship);
    return OK;
}

/*
 * This function is used to get the ship at a given position.
 * @param board the board where the ship is.
 * @param x the x coordinate of the tile.
 * @param y the y coordinate of the tile.
 * @return a pointer to the ship at the given position.
 */
Ship*
get_ship_at(Board* board, int x, int y) {
    int error, head_x, head_y;
    /* Check if the coordinates are in bounds */
    error = is_in_bounds(board, x, y);
    if (ERROR_TILE_OUT_OF_BOUNDS == error) {
        return NULL;
    }
    /* Get the head of the ship */
    if (TILE_STATE_SHIP != board->tiles[x][y].state) {
        return NULL;
    }

    head_x = board->tiles[x][y].ship_head[0];
    head_y = board->tiles[x][y].ship_head[1];
    return board->tiles[head_x][head_y].ship;
}
