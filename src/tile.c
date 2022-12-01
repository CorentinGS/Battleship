/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Battleship                             ______   _______      _______.      *
 * main.c                                /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: BSD-3                                                      /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#include "tile.h"

/*
 * This function is used to initialize the tile in memory.
 */
void
init_tile(Tile* tile) {
    tile->state = TILE_STATE_EMPTY;
    tile->ship = NULL;
}

/*
 * This function is used to set the state of a tile.
 */
void
set_tile_state(Tile* tile, TileState state) {
    tile->state = state;
}

/*
 * This function is used to set the ship of a tile.
 */
void
set_tile_ship(Tile* tile, Ship* ship) {
    tile->state = TILE_STATE_SHIP;
    tile->ship = ship;
}

/*
 * This function is used to free the tile in memory.
 */
void
free_tile(Tile* tile) {
    tile->state = TILE_STATE_EMPTY;
    if (tile->ship != NULL) {
        free(tile->ship);
    }
    tile->ship = NULL;
}
