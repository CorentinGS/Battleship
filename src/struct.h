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
    char* name;
    PlayerType type;
} Player;

/* Ship */
typedef struct {
    ShipType type;
    Orientation orientation;
    int* head;
    int id;
} Ship;

/* Tile */
typedef struct {
    TileState state;
    Ship* ship;
    int* ship_head;
} Tile;

/* Board */
typedef struct {
    Tile** tiles;
} Board;

/* Game structure */
typedef struct {
    Board board1;
    Board board2;
    Player player1;
    Player player2;
    GameMode mode;
    GameState state;
    GameTurn turn;
    GameWinner winner;
} Game;

/* Scenario element */
typedef struct {
    ScenarioElementType type;
    int x;
    int y;
    ShipType ship_type;
    Orientation orientation;
    Board *board;
    GameDirection direction;
} ScenarioElement;

#endif
