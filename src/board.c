/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Battleship                             ______   _______      _______.      *
 * board.c                               /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: BSD-3                                                      /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#include <string.h>
#include "board.h"
#include "ship.h"

/*
 * This function is used to initialize the board in memory.
 */
void
init_board(Board* board) {
    int i, j;

    /* malloc the board */
    board->tiles = malloc(sizeof(Tile) * BOARD_WIDTH);

    /* malloc the tiles */
    for (i = 0; i < BOARD_WIDTH; ++i) {
        board->tiles[i] = malloc(sizeof(Tile) * BOARD_HEIGHT);
    }

    /* init the tiles */
    for (i = 0; i < BOARD_WIDTH; ++i) {
        for (j = 0; j < BOARD_HEIGHT; ++j) {
            init_tile(&board->tiles[i][j]);
        }
    }
}

/*
 * This function is used to create a ship at a given position.
 */

int
add_ship(Board* board, ShipType type, int x, int y, Orientation orientation) {
    int i;
    int x2 = x;
    int y2 = y;
    Ship* ship;

    /* check if the ship is out of bounds */
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
        fprintf(stderr, "The ship is out of bounds.\n");
        return ERROR_SHIP_OUT_OF_BOUNDS;
    }

    /* check if the ship is out of bounds */
    if (ORIENTATION_HORIZONTAL == orientation) {
        x2 += get_ship_size(type) - 1;
        if (x2 < 0 || x2 >= BOARD_WIDTH) {
            fprintf(stderr, "The ship is out of bounds.\n");
            return ERROR_SHIP_OUT_OF_BOUNDS;
        }
    } else {
        y2 += get_ship_size(type) - 1;
        if (y2 < 0 || y2 >= BOARD_HEIGHT) {
            fprintf(stderr, "The ship is out of bounds.\n");
            return ERROR_SHIP_OUT_OF_BOUNDS;
        }
    }

    /* check if the ship is already placed */
    for (i = 0; i < get_ship_size(type); ++i) {
        if (board->tiles[x][y].state == TILE_STATE_SHIP) {
            fprintf(stderr, "The ship is already placed.\n");
            return ERROR_SHIP_OVERLAP;
        }
        if (ORIENTATION_HORIZONTAL == orientation) {
            ++x;
        } else {
            ++y;
        }
    }

    /* create the ship */
    /* Remember to free the ship */
    ship = create_ship();

    set_ship(ship, type, orientation);

    /* place the ship */
    x = x2;
    y = y2;
    for (i = 0; i < get_ship_size(type); ++i) {
        set_tile_ship(&board->tiles[x][y], ship);
        if (ORIENTATION_HORIZONTAL == orientation) {
            --x;
        } else {
            --y;
        }
    }

    return OK;
}

/*
 * This function is used to free the board in memory.
 */
void
free_board(Board* board) {
    int i, j;
    for (i = 0; i < BOARD_WIDTH; ++i) {
        for (j = 0; j < BOARD_HEIGHT; ++j) {
            free_tile(&board->tiles[i][j]);
        }
        if (NULL != board->tiles[i]) {
            free(board->tiles[i]);
        }
    }
    if (NULL != board->tiles) {
        free(board->tiles);
    }
}
