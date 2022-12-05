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

#include "bomb.h"
#include "board.h"
#include "ship.h"

/*
 * This function is used to place a bomb on the map.
 * If the bomb is placed on a ship, the ship is hit. If the ship is destroyed, the ship is removed from the map.
 * If the bomb is placed on the water, the bomb is placed on the map.
 * If the bomb is placed on a bomb, the bomb is not placed on the map.
 * @param board The board on which the bomb is placed.
 * @param x The x coordinate of the bomb.
 * @param y The y coordinate of the bomb.
 * @return 0 if the bomb is placed on the map
 */
int
place_bomb(Board* board, int x, int y) {
    Tile* tile;
    int error;
    error = is_in_bounds(x, y);
    if (ERROR_TILE_OUT_OF_BOUNDS == error) {
        return error;
    }

    tile = &board->tiles[x][y];

    if (TILE_STATE_BOMB == tile->state) {
        return INFO_BOMB_OVERLAP;
    }
    if (TILE_STATE_SHIP == tile->state) {
        error = hit_ship(board, x, y);
        return error;
    }
    tile->state = TILE_STATE_BOMB;

    return OK;
}
