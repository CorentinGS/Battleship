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

#ifndef BATTLESHIP_TILE_H
#define BATTLESHIP_TILE_H

#include "common.h"

#include "ship.h"

extern void init_tile(Tile* tile);
extern void set_tile_state(Tile* tile, TileState state);
extern void set_tile_ship(Tile* tile, Ship* ship);
extern void set_tile_ship_head(Tile* tile, int x, int y);
extern void free_tile(Board* board, int x, int y);
extern void print_tile(Tile* tile);
extern void print_tile_hidden(Tile* tile);

#endif
