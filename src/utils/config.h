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

#define SET_BOARD_WIDTH(x) (BOARD_WIDTH = x)
#define SET_BOARD_HEIGHT(y) (BOARD_HEIGHT = y)

int BOARD_WIDTH = 10;
int BOARD_HEIGHT = 10;

#define FRIGATE_COUNT      1
#define DESTROYER_COUNT    1
#define SHIP_CRUISER_COUNT 1
#define CARRIER_COUNT      0

#define NUMBER_OF_SHIPS    (FRIGATE_COUNT + DESTROYER_COUNT + SHIP_CRUISER_COUNT + CARRIER_COUNT)

#endif
