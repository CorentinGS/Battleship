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

/*
 * This function is used to initialize the board in memory.
*/
void
init_board(Board* board) {
    /* malloc the board */
    board->tiles = malloc(sizeof(Tile) * BOARD_WIDTH);

    /* malloc the tiles */
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        board->tiles[i] = malloc(sizeof(Tile) * BOARD_HEIGHT);
    }

    /* init the tiles */
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        for (int j = 0; j < BOARD_HEIGHT; ++j) {
            init_tile(&board->tiles[i][j]);
        }
    }
}

/*
 * This function is used to free the board in memory.
*/
void
free_board(Board* board) {
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        for (int j = 0; j < BOARD_HEIGHT; ++j) {
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
