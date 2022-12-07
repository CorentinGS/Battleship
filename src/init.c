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

#include <string.h>
#include "init.h"
#include "board.h"
#include "player.h"
#include "utils/utils.h"
#include "ship.h"
#include "io.h"

static void init_boards(void);

static void init_game_mode(void);
static int init_players(void);
static int init_ships(Board* board);

int
init_game(void) {
    init_boards();
    init_game_mode();
}

static void
init_boards(void) {
    /* Init the board. */
    init_board(&game.board1);

    /* Init the board. */
    init_board(&game.board2);

    /* Init the game mode. */
    init_game_mode();

    /* Init the players. */
    init_players();

    /* Init the ships. */
    init_ships(&game.board1);
    init_ships(&game.board2);
}

static void
init_game_mode(void) {
    int ch;
    int game_mode;

    /* Get the game mode. */
    printf("Please enter the game mode (1 for PvP, 2 for PvE): ");
    /* Check for scanf errors. */
    if (scanf("%d", &game_mode) != 1) {
        printf("Error: scanf failed. Please enter a valid game mode.\n");
        init_game_mode();
    }

    /* clear the buffer */

    while (((ch = getchar()) != EOF) && (ch != '\n')) {
        ;
    }

    /* Check if the game mode is valid. */
    if (game.mode != 1 && game.mode != 2) {
        printf("Error: Invalid game mode. Please enter a valid game mode.\n");
        init_game_mode();
    }

    /* Set the game mode. */
    game.mode = 1 == game.mode ? GAME_MODE_MULTI : GAME_MODE_SINGLE;

    /* Clear the stdin buffer. */
    fflush(stdin);

    /* Print the game mode. */
    printf("Game mode: %s\n", game.mode == GAME_MODE_MULTI ? "PvP" : "PvE");
}

static int
init_players(void) {
    int err;
    char* name;
    Player player1, player2;

    player1 = create_player();
    player2 = create_player();

    name = malloc(sizeof(char) * MAX_NAME_SIZE);

    /* Init the players. */
    err = get_player_name(name, MAX_NAME_SIZE);
    if (OK != err) {
        printf("Error: Couldn't get the name\n");
        if (NULL != name) {
            free(name);
        }
        return ERROR;
    }

    /* Set the player's name. */
    strcpy(player1.name, name);

    if (GAME_MODE_MULTI == game.mode) {
        /* Init the players. */
        err = get_player_name(name, MAX_NAME_SIZE);
        if (OK != err) {
            printf("Error: Couldn't get the name\n");
            if (NULL != name) {
                free(name);
            }
            return ERROR;
        }

        /* Set the player's name. */
        strcpy(player2.name, name);
    } else {
        /* Set the ai's name. */
        get_random_ai_name(player2.name);
        player2.type = PLAYER_TYPE_AI;
    }

    /* Set the players. */
    game.player1 = player1;
    game.player2 = player2;

    /* Free the name. */
    if (NULL != name) {
        free(name);
    }

    return OK;
}

static int
init_ships(Board* board) {
    int err;
    int i;
    int* coords;
    int ship_count;
    Ship* ship;

    coords = malloc(sizeof(int) * 2);

    /* Init the ships. */
    err = add_ship(board, SHIP_FRIGATE, 0, 0, ORIENTATION_HORIZONTAL);
    if (OK != err) {
        printf("Error: Couldn't add the ship\n");
        return ERROR;
    }

    err = add_ship(board, SHIP_DESTROYER, 4, 6, ORIENTATION_VERTICAL);
    if (OK != err) {
        printf("Error: Couldn't add the ship\n");
        return ERROR;
    }

    err = add_ship(board, SHIP_CRUISER, 2, 2, ORIENTATION_HORIZONTAL);
    if (OK != err) {
        printf("Error: Couldn't add the ship\n");
        return ERROR;
    }

    err = add_ship(board, CARRIER_COUNT, 6, 4, ORIENTATION_VERTICAL);
    if (OK != err) {
        printf("Error: Couldn't add the ship\n");
        return ERROR;
    }
    return OK;
}
