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

#include "game.h"
#include "io.h"
#include "bomb.h"
#include "ai.h"

#define forever       for (;;)
#define CHANGE_PLAYER (game->turn = (game->turn + 1) % 2)

static int game_action_fire(Board* board);
static int game_action_move(Board* board);

int
game_loop(Game* game) {
    int *coords, err, action;
    coords = malloc_prof(sizeof(int) * 2);
    display_header(game);
    forever {
        if (game->turn == GAME_TURN_PLAYER1) {
            action = ask_action();
            if (GAME_ACTION_FIRE == action) {
                game_action_fire(&game->board2);
            } else if (GAME_ACTION_MOVE == action) {
                game_action_move(&game->board1);
            }

            if (0 == check_ships(&game->board2)) {
                game->state = GAME_STATE_END;
                game->winner = GAME_WINNER_PLAYER1;
                break;
            }

            CHANGE_PLAYER;
        } else {
            display_board_hidden(&game->board1);
            select_random_position(coords);
            err = place_bomb(&game->board1, coords[0], coords[1]);
            if (err != OK) {
                printf("You already bombed this place!\n");
                continue;
            }
            if (0 == check_ships(&game->board1)) {
                game->state = GAME_STATE_END;
                game->winner = GAME_WINNER_PLAYER2;
                break;
            }
            CHANGE_PLAYER;
        }
    }

    printf("Game over!\nWinner: %u\n", game->winner);

    free_prof(coords);

    return 0;
}

static int
game_action_fire(Board* board) {
    int *coords, err;
    coords = malloc_prof(sizeof(int) * 2);

    display_board_hidden(board);

    ask_coordinates(coords);

    err = place_bomb(board, coords[0], coords[1]);
    if (err != OK) {
        switch (err) {
            case ERROR_TILE_OUT_OF_BOUNDS:
                printf("Coordinates out of bounds!\n");
                break;
            case INFO_BOMB_OVERLAP:
                printf("You already bombed this place!\n");
                break;
            default:
                printf("Unknown error!\n");
                break;
        }
    }

    free_prof(coords);
    return OK;
}

static int
game_action_move(Board* board) {
    int *coords, err, vector;
    Ship* ship;
    coords = malloc_prof(sizeof(int) * 2);

    display_board(board);

    printf("Select the ship you want to move:\n");

    ask_coordinates(coords);

    ship = get_ship_at(board, coords[0], coords[1]);

    vector = ask_move_vector();

    err = move_ship(board, ship, vector);
    if (err != OK) {
        printf("You can't move this ship here!\n");
        return err;
    }

    return OK;
}
