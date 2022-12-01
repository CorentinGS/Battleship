/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Battleship                             ______   _______      _______.      *
 * struct.h                              /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: BSD-3                                                      /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#ifndef BATTLESHIP_STRUCT_H
#define BATTLESHIP_STRUCT_H

#include "utils/const.h"

/* Player structure */
typedef struct {
    char name[MAX_NAME_SIZE];
    int score;
} Player;

/* Board */
typedef struct {
    int size;
    int** board;
} Board;


/* Ship */
typedef struct {
    int size;
    int x;
    int y;
    int orientation;
} Ship;


#endif //BATTLESHIP_STRUCT_H
