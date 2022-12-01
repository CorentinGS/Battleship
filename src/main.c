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
#include <malloc.h>
#include <string.h>

static void onClosing(void);

int
main(int argc, char* argv[]) {
    char* name = malloc(sizeof(char) * MAX_NAME_SIZE);
    get_player_name(name, MAX_NAME_SIZE);
    printf("Hello %s", name);

    memset(&game, 0, sizeof(game));

    init_board(&game.board);

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
