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

#define MAX_NAME_SIZE      100

#define TRUE               (1 == 1)
#define FALSE              (!TRUE)

#define RELEASE_MODE       0
#define DEBUG_MODE         1

#define COORDINATE_SIZE    2

#define FILE_BUFFER_SIZE   256

#define ANSI_COLOR_RED     "\033[0;31m"
#define ANSI_COLOR_GREEN   "\033[0;32m"
#define ANSI_COLOR_YELLOW  "\033[0;33m"
#define ANSI_COLOR_BLUE    "\033[0;34m"
#define ANSI_COLOR_MAGENTA "\033[0;35m"
#define ANSI_COLOR_CYAN    "\033[0;36m"
#define ANSI_COLOR_WHITE   "\033[0;37m"
#define ANSI_COLOR_RESET   "\033[0m"

/* Tile states enum */
typedef enum { TILE_STATE_EMPTY, TILE_STATE_SHIP, TILE_STATE_HIT, TILE_STATE_BOMB } TileState;

/* Scenario elements enum */
typedef enum { SCENARIO_ELEMENT_PLACE_SHIP, SCENARIO_ELEMENT_SHOOT, SCENARIO_ELEMENT_MOVE, SCENARIO_ELEMENT_DISPLAY } ScenarioElementType;

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
    ERROR_SHIP_OVERLAP,
    ERROR_SHIP_CREATION,
    INFO_BOMB_OVERLAP,
    ERROR_TILE_OUT_OF_BOUNDS,
    INFO_TILE_ALREADY_HIT,
    ERROR_TILE_NOT_SHIP,
    ERROR_CANNOT_OPEN_FILE,
    ERROR_CANNOT_READ_FILE,
    ERROR_CANNOT_CLOSE_FILE,
    ERROR_CANNOT_ALLOCATE_MEMORY
} ERROR_CODE;

typedef enum game_state { GAME_STATE_RUNNING, GAME_STATE_END } GameState;

typedef enum game_mode { GAME_MODE_SINGLE, GAME_MODE_MULTI } GameMode;

typedef enum player_type { PLAYER_TYPE_HUMAN, PLAYER_TYPE_AI } PlayerType;

typedef enum game_turn { GAME_TURN_PLAYER1, GAME_TURN_PLAYER2 } GameTurn;

typedef enum game_winner { IN_PROGRESS, GAME_WINNER_PLAYER1, GAME_WINNER_PLAYER2, GAME_WINNER_DRAW } GameWinner;

typedef enum game_action { GAME_ACTION_FIRE, GAME_ACTION_MOVE } GameAction;

typedef enum game_direction { GAME_DIRECTION_BACKWARD = -1, GAME_DIRECTION_NONE, GAME_DIRECTION_FORWARD } GameDirection;

#endif
