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
#include "ship.h"

/*
 * This function is used to initialize the tile in memory.
 */
void
init_tile(Tile* tile) {
    tile->state = TILE_STATE_EMPTY;
    tile->ship = NULL;
    tile->ship_head = NULL;
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
    if (NULL != tile->ship_head) {
        free(tile->ship_head);
    }
    tile->ship_head = malloc(sizeof(tile->ship_head) * COORDINATE_SIZE);
    tile->ship_head[0] = ship->head[0];
    tile->ship_head[1] = ship->head[1];
}

void
set_tile_ship_head(Tile* tile, int x, int y) {
    tile->state = TILE_STATE_SHIP;
    if (NULL != tile->ship_head) {
        free(tile->ship_head);
    }
    tile->ship = NULL;
    tile->ship_head = malloc(sizeof(tile->ship_head) * COORDINATE_SIZE);
    tile->ship_head[0] = x;
    tile->ship_head[1] = y;
}

/*
 * This function is used to free the tile in memory.
 */
void
free_tile(Board* board, int x, int y) {
    Tile* tile;

    tile = &board->tiles[x][y];
    if (NULL != tile->ship_head) {
        free(tile->ship_head);
    }

    if (TILE_STATE_SHIP == tile->state || TILE_STATE_HIT == tile->state) {
        if (NULL != tile->ship) {
            free_ship(tile->ship);
        }
    }
    tile->state = TILE_STATE_EMPTY;
    tile->ship = NULL;
}

/*
 * This function is used to print the tile.
 */
void
print_tile(Tile* tile) {
    switch (tile->state) {
        case TILE_STATE_EMPTY:
            printf("_ ");
            break;
        case TILE_STATE_SHIP:
            printf(ANSI_COLOR_BLUE "S " ANSI_COLOR_RESET);
            break;
        case TILE_STATE_BOMB:
            printf("B ");
            break;
        case TILE_STATE_HIT:
            printf("H ");
            break;
        default:
            printf(" ");
            break;
    }
}

/*
 * This function is used to check if the tile is a ship.
 */
int
is_tile_ship(Tile* tile) {
    return TILE_STATE_SHIP == tile->state;
}
