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

int
game_loop(Game* game) {
    int *coords, err;
    coords = malloc_prof(sizeof(int) * 2);
    display_header(game);
    forever {
        if (game->turn == GAME_TURN_PLAYER1) {
            display_board_hidden(&game->board2);
            ask_coordinates(coords);

            err = place_bomb(&game->board2, coords[0], coords[1]);
            if (err != OK) {
                printf("You already bombed this place!\n");
                continue;
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
