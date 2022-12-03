/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Battleship                             ______   _______      _______.      *
 * const.h                               /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: BSD-3                                                      /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#ifndef BATTLESHIP_CONST_H
#define BATTLESHIP_CONST_H

#define MAX_NAME_SIZE 100

/* Tile states enum */
typedef enum { TILE_STATE_EMPTY, TILE_STATE_SHIP, TILE_STATE_HIT, TILE_STATE_BOMB } TileState;

/* Ship size enum */
typedef enum ship_size {
    SHIP_FRIGATE_SIZE = 1,
    SHIP_DESTROYER_SIZE = 2,
    SHIP_CRUISER_SIZE = 3,
    SHIP_CARRIER_SIZE = 4
} ShipSize;

typedef enum ship_type { SHIP_NONE, SHIP_FRIGATE, SHIP_DESTROYER, SHIP_CRUISER, SHIP_CARRIER } ShipType;

typedef enum orientation { ORIENTATION_HORIZONTAL, ORIENTATION_VERTICAL } Orientation;

typedef enum error {
    OK,
    ERROR,
    ERROR_SHIP_OUT_OF_BOUNDS,
    ERROR_SHIP_OVERLAP
} ERROR_CODE;

#endif
