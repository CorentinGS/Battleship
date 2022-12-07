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

#include "init.h"

static void init_boards(void);
static void init_game_mode(void);
static int init_players(void);
static int init_ships(Board* board);

int
init_game(void) {
    init_boards();
    init_game_mode();
    /* Init the ships. */
    init_ships(&game.board1);
    init_ships(&game.board2);
    return init_players();
}

static void
init_boards(void) {
    /* Init the board. */
    init_board(&game.board1);

    /* Init the board. */
    init_board(&game.board2);
}

static void
init_game_mode(void) {
    int ch;
    int game_mode;

    /* Get the game mode. */
    printf("Please enter the game mode (1 for PvP, 2 for PvE): ");
    /* Check for scanf errors. */

    do {
        scanf("%d", &game_mode);
        /* Clear the input buffer. */
        while ((ch = getchar()) != '\n' && ch != EOF) {
            ;
        }

    } while (game_mode != 1 && game_mode != 2);

    /* Set the game mode. */
    game.mode = 1 == game_mode ? GAME_MODE_MULTI : GAME_MODE_SINGLE;

    /* Clear the stdin buffer. */
    fflush(stdin);

    /* Print the game mode. */
    printf("Game mode: %d\n", game.mode);
}

static int
init_players(void) {
    int err;
    char* name;
    Player *player1, *player2;

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
    strcpy(player1->name, name);

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
        strcpy(player2->name, name);
    } else {
        /* Set the ai's name. */
        get_random_ai_name(player2->name);
        player2->type = PLAYER_TYPE_AI;
    }

    /* Set the players. */
    game.player1 = *player1;
    game.player2 = *player2;

    /* Free the name. */
    if (NULL != name) {
        free(name);
    }

    /* Free the players. */
    if (NULL != player1) {
        free(player1);
    }

    /* Free the players. */
    if (NULL != player2) {
        free(player2);
    }

    return OK;
}

static int
init_ships(Board* board) {
    int err;
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

    err = add_ship(board, SHIP_CARRIER, 6, 4, ORIENTATION_VERTICAL);
    if (OK != err) {
        printf("Error: Couldn't add the ship\n");
        return ERROR;
    }
    return OK;
}
