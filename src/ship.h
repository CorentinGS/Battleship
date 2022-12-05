/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Battleship                             ______   _______      _______.      *
 * ship.h                                /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: BSD-3                                                      /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#ifndef BATTLESHIP_SHIP_H
#define BATTLESHIP_SHIP_H

#include "common.h"

extern void free_ship(Ship* ship);
extern Ship* create_ship(void);
extern void set_ship(Ship* ship, ShipType type, Orientation orientation, int x, int y);
extern void set_ship_type(Ship* ship, ShipType type);
extern void set_ship_orientation(Ship* ship, Orientation orientation);
extern int get_ship_size(ShipType type);
extern int is_ship_destroyed(Ship* ship, Board* board);
extern int hit_ship(Board* board, int x, int y);
extern int remove_ship(Board* board, Ship* ship);
extern Ship* get_ship_at(Board* board, int x, int y);
extern int get_ships(Board* board, int** ships);
extern int check_ships(Board* board);

#endif
