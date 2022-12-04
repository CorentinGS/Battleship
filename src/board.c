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
 * It returns 0 if the ship was created successfully.
 * It returns ERROR_SHIP_OUT_OF_BOUNDS if the ship is out of bounds.
 * It returns ERROR_SHIP_OVERLAP if the ship overlaps another ship.
 */
int
add_ship(Board* board, ShipType type, int x, int y, Orientation orientation) {
    int i, hx, hy;
    int x2 = x;
    int y2 = y;
    Ship* ship;

    /* check if the ship is out of bounds */
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
        fprintf(stderr, ANSI_COLOR_WHITE "The ship is out of bounds.\n" ANSI_COLOR_RESET);
        return ERROR_SHIP_OUT_OF_BOUNDS;
    }

    /* check if the ship is out of bounds */
    if (ORIENTATION_HORIZONTAL == orientation) {
        x2 += get_ship_size(type) - 1;
        if (x2 < 0 || x2 >= BOARD_WIDTH) {
            fprintf(stderr, ANSI_COLOR_WHITE "The ship is out of bounds.\n" ANSI_COLOR_RESET);
            return ERROR_SHIP_OUT_OF_BOUNDS;
        }
    } else {
        y2 += get_ship_size(type) - 1;
        if (y2 < 0 || y2 >= BOARD_HEIGHT) {
            fprintf(stderr, ANSI_COLOR_WHITE "The ship is out of bounds.\n" ANSI_COLOR_RESET);
            return ERROR_SHIP_OUT_OF_BOUNDS;
        }
    }

    /* check if the ship is already placed */
    for (i = 0; i < get_ship_size(type); ++i) {
        if (board->tiles[x][y].state == TILE_STATE_SHIP) {
            fprintf(stderr, ANSI_COLOR_WHITE "The ship is already placed.\n" ANSI_COLOR_RESET);
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

    if (NULL == ship) {
        fprintf(stderr, ANSI_COLOR_WHITE "Failed to create the ship.\n" ANSI_COLOR_RESET);
        return ERROR_SHIP_CREATION;
    }

    if (ORIENTATION_HORIZONTAL == orientation) {
        hx = x2 - get_ship_size(type) + 1;
        hy = y2;
    } else {
        hx = x2;
        hy = y2 - get_ship_size(type) + 1;
    }
    set_ship(ship, type, orientation, hx, hy);

    /* place the head */
    set_tile_ship(&board->tiles[hx][hy], ship);
    /* place the body */
    for (i = 1; i < get_ship_size(type); ++i) {
        set_tile_ship_head(&board->tiles[x2][y2], ship->head[0], ship->head[1]);
        if (ORIENTATION_HORIZONTAL == orientation) {
            --x2;
        } else {
            --y2;
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
            free_tile(board, i, j);
        }
        if (NULL != board->tiles[i]) {
            free(board->tiles[i]);
        }
    }
    if (NULL != board->tiles) {
        free(board->tiles);
    }
}

/*
 * This function is used to print the board.
 * It prints the board in the console.
 * It's used for debugging.
 */
void
print_board(Board* board) {
    int y, x;
    for (y = 0; y < BOARD_HEIGHT; ++y) {
        for (x = 0; x < BOARD_WIDTH; ++x) {
            print_tile(&board->tiles[x][y]);
        }
        printf("\n");
    }
}

int
is_in_bounds(Board* board, int x, int y) {
    if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
        return ERROR_TILE_OUT_OF_BOUNDS;
    }
    return OK;
}

/*
 * This function is used to display the board with coordinates and ships.
 * It prints the board in the console.
 * Coordinates are displayed on the left and on the top.
 */
void
display_board(Board* board) {
    int y, x;
    printf("    ");
    for (x = 0; x < BOARD_WIDTH; ++x) {
        printf("%c ", 'A' + x);
    }
    /* Add spacer */
    printf("\n");
    printf("  ");
    for (x = 0; x < BOARD_WIDTH; ++x) {
        printf("--");
    }
    printf("\n");

    for (y = 0; y < BOARD_HEIGHT; ++y) {
        /* Display the y coordinate using 2 digits */
        printf("%02d| ", y + 1);
        for (x = 0; x < BOARD_WIDTH; ++x) {
            print_tile(&board->tiles[x][y]);
        }
        printf("\n");
    }
}
