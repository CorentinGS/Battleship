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


#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10

#define MAX_INPUT_SIZE ((BOARD_HEIGHT >= 9) ? (4) : (3))

#define FRIGATE_COUNT      1
#define DESTROYER_COUNT    1
#define SHIP_CRUISER_COUNT 1
#define CARRIER_COUNT      0

#define NUMBER_OF_SHIPS    (FRIGATE_COUNT + DESTROYER_COUNT + SHIP_CRUISER_COUNT + CARRIER_COUNT)

#endif
