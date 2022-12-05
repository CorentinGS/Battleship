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

#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H

#include "common.h"
#include "tile.h"

extern void init_board(Board* board);
extern void free_board(Board* board);
extern void print_board(Board* board);
extern void display_board(Board* board);
extern void display_board_hidden(Board* board);
extern int add_ship(Board* board, ShipType type, int x, int y, Orientation orientation);
extern int is_in_bounds(Board* board, int x, int y);

#endif
