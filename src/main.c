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
#include "test/test_handler.h"
#include <malloc.h>
#include <string.h>

static void onClosing(void);
static int get_debug_mode(void);
static void run_debug_mode(void);

#define IS_DEBUG_MODE (TRUE == get_debug_mode())

int
main(int argc, char* argv[]) {
    int err;
    char* name;

    /* if (IS_DEBUG_MODE) { */
    if (IS_DEBUG_MODE) {
        printf("Debug mode is enabled\n");
        run_debug_mode();
        return OK;
    }

    name = malloc(sizeof(char) * MAX_NAME_SIZE);
    err = get_player_name(name, MAX_NAME_SIZE);
    if (1 == err) {
        printf("Error: Couldn't get the name\n");
        return 1;
    }

    printf("Hello %s\n", name);

    memset(&game, 0, sizeof(game));

    init_board(&game.board);

    /* Add a ship to the board */
    err = add_ship(&game.board, SHIP_CARRIER, 0, 0, ORIENTATION_HORIZONTAL);
    if (OK != err) {
        printf("Error: Couldn't add the ship\n");
        return 1;
    }

    print_board(&game.board);

    atexit(onClosing);

    free(name);

    return 0;
}

static void
run_debug_mode(void) {
    printf("--------------------------------\n");
    printf(ANSI_COLOR_BLUE "Running tests ⤵️\n" ANSI_COLOR_RESET);
    run_tests();
    printf("--------------------------------\n");
    printf(ANSI_COLOR_GREEN "Tests finished with no errors ✅\n" ANSI_COLOR_RESET);
}

static int
get_debug_mode(void) {
    char* debug;
    debug = getenv("MODE");
    if (NULL == debug) {
        return RELEASE_MODE;
    }
    if (OK == strcmp(debug, "debug")) {
        return DEBUG_MODE;
    }
    return RELEASE_MODE;
}

static void
onClosing(void) {
    printf("Closing the game...\n");
    free_board(&game.board);
    printf("Game closed.\n");
}
