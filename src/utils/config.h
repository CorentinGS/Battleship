/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Battleship                             ______   _______      _______.      *
 * config.h                              /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: BSD-3                                                      /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#ifndef BATTLESHIP_CONFIG_H
#define BATTLESHIP_CONFIG_H

#define BOARD_WIDTH        10
#define BOARD_HEIGHT       10

#define FRIGATE_COUNT      3
#define DESTROYER_COUNT    2
#define SHIP_CRUISER_COUNT 2
#define CARRIER_COUNT      1

/* Ship size enum */
typedef enum ship_size {
    SHIP_FRIGATE_SIZE = 1,
    SHIP_DESTROYER_SIZE = 2,
    SHIP_CRUISER_SIZE = 3,
    SHIP_CARRIER_SIZE = 4
} ShipSize;

#endif //BATTLESHIP_CONFIG_H
