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

#include "main.h"

#include "utils/const.h"
#include "player.h"
#include "board.h"
#include "ship.h"
#include <malloc.h>
#include <string.h>

static void onClosing(void);

int
main(int argc, char* argv[]) {
    int err;
    char* name = malloc(sizeof(char) * MAX_NAME_SIZE);
    err = get_player_name(name, MAX_NAME_SIZE);
    if (1 == err) {
        printf("Error: Couldn't get the name\n");
        return 1;
    }

    printf("Hello %s\n", name);

    memset(&game, 0, sizeof(game));

    init_board(&game.board);

    /* Add a ship to the board */
    err = add_ship(&game.board, SHIP_FRIGATE, 0, 0, ORIENTATION_HORIZONTAL);
    if (OK != err) {
        printf("Error: Couldn't add the ship\n");
        return 1;
    }

    atexit(onClosing);

    free(name);

    return 0;
}

static void
onClosing(void) {
    printf("Closing the game...\n");
    free_board(&game.board);
    printf("Game closed.\n");
}
