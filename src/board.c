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

#include "board.h"

/*
 * This function is used to initialize the board in memory.
 */
void
init_board(Board* board) {
    int i, j;

    /* malloc_prof the board */
    board->tiles = malloc_prof(sizeof(Tile) * BOARD_WIDTH);

    /* malloc_prof the tiles */
    for (i = 0; i < BOARD_WIDTH; ++i) {
        board->tiles[i] = malloc_prof(sizeof(Tile) * BOARD_HEIGHT);
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
        if (TILE_STATE_SHIP == board->tiles[x][y].state) {
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
    /* Remember to free_prof the ship */
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
 * This function is used to free_prof the board in memory.
 */
void
free_prof_board(Board* board) {
    int i, j;
    for (i = 0; i < BOARD_WIDTH; ++i) {
        for (j = 0; j < BOARD_HEIGHT; ++j) {
            free_prof_tile(board, i, j);
        }
        if (NULL != board->tiles[i]) {
            free_prof(board->tiles[i]);
        }
    }
    if (NULL != board->tiles) {
        free_prof(board->tiles);
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
is_in_bounds(int x, int y) {
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

/*
 * This function is used to display the board with coordinates but hidden ships.
 * It prints the board in the console.
 * Coordinates are displayed on the left and on the top.
 */
void
display_board_hidden(Board* board) {
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
            print_tile_hidden(&board->tiles[x][y]);
        }
        printf("\n");
    }
}

/*
 * This function is used to return the coordinates of every ship on the board.
 * It returns the number of ships.
 * It returns the ships in the ships array.
 * The ships array must be allocated and free_profd by the caller.
 */
int
get_ships(Board* board, int** ships) {
    int i, j, id;
    int count = 0;
    int* ship;

    int* excluded;

    excluded = (int*)malloc_prof(sizeof(int) * NUMBER_OF_SHIPS);

    for (i = 0; i < BOARD_WIDTH; ++i) {
        for (j = 0; j < BOARD_HEIGHT; ++j) {
            if (TILE_STATE_SHIP == board->tiles[i][j].state) {
                if (TILE_STATE_SHIP == board->tiles[i][j].state) {
                    /* check if the id is in the excluded list */
                    id = get_ship_at(board, i, j)->id;
                    if (!is_in_array(excluded, NUMBER_OF_SHIPS, id)) {
                        excluded[count++] = id;
                        ships[count - 1][0] = i;
                        ships[count - 1][1] = j;
                    }
                }
            }
        }
    }

    if (NULL != excluded) {
        free_prof(excluded);
    }

    return count;
}

/*
 * This function is used to check if there are any ships left on the board.
 * It returns the number of ships left.
 */
int
check_ships(Board* board) {
    int i, j, id, count, found;
    int* excluded;
    Ship* ship;

    excluded = (int*)malloc_prof(sizeof(int) * NUMBER_OF_SHIPS);
    /* set excluded to -1 */
    for (i = 0; i < NUMBER_OF_SHIPS; ++i) {
        excluded[i] = -1;
    }

    count = 0;
    for (i = 0; i < BOARD_WIDTH; ++i) {
        for (j = 0; j < BOARD_HEIGHT; ++j) {
            if (TILE_STATE_SHIP == board->tiles[i][j].state) {
                /* check if the id is in the excluded list */
                ship = get_ship_at(board, i, j);
                if (NULL == ship) {
                    printf("Error: ship is NULL at %d, %d in check_ships function in board.c file. Exiting.\n", i, j);
                    exit(1);
                }
                id = ship->id;
                found = is_in_array(excluded, NUMBER_OF_SHIPS, id);
                if (!found) {
                    excluded[count++] = id;
                }
            }
        }
    }

    if (NULL != excluded) {
        free_prof(excluded);
    }

    return count;
}
