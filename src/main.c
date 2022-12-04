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
#include "bomb.h"
#include "io.h"
#include <malloc.h>
#include <string.h>

static void onClosing(void);
static int get_debug_mode(void);
static void run_debug_mode(void);

/* Macro to determine if the program is running in debug mode. */
#define IS_DEBUG_MODE (TRUE == get_debug_mode())

/*
 * Main function.
 */
int
main(int argc, char* argv[]) {
    int err;
    char* name;
    int* coords;

    /* If the program is running in debug mode, run the tests. */
    if (IS_DEBUG_MODE) {
        printf("Debug mode is enabled\n");
        run_debug_mode();
        return OK;
    }

    /* Get the player's name. */
    name = malloc(sizeof(char) * MAX_NAME_SIZE);
    err = get_player_name(name, MAX_NAME_SIZE);
    if (1 == err) {
        printf("Error: Couldn't get the name\n");
        return 1;
    }

    printf("Hello %s\n", name);

    /* Memset the game structure. */
    memset(&game, 0, sizeof(game));

    /* Init the board. */
    init_board(&game.board1);

    /* Add a ship to the board */
    err = add_ship(&game.board1, SHIP_CARRIER, 0, 0, ORIENTATION_HORIZONTAL);
    if (OK != err) {
        printf("Error: Couldn't add the ship\n");
        return 1;
    }

    err = place_bomb(&game.board1, 0, 0);
    if (OK != err) {
        printf("Error: Couldn't place the bomb\n");
        return 1;
    }

    /* Display the board. */
    display_board(&game.board1);

    err = place_bomb(&game.board1, 1, 0);
    if (OK != err) {
        printf("Error: Couldn't place the bomb\n");
        return 1;
    }
    err = place_bomb(&game.board1, 2, 0);
    if (OK != err) {
        printf("Error: Couldn't place the bomb\n");
        return 1;
    }
    err = place_bomb(&game.board1, 3, 0);
    if (OK != err) {
        printf("Error: Couldn't place the bomb\n");
        return 1;
    }

    coords = malloc(sizeof(int) * 2);
    ask_coordinates(coords);

    place_bomb(&game.board1, coords[0], coords[1]);
    if (NULL != coords) {
        free(coords);
    }

    display_board(&game.board1);

    /* Free on exit. */
    atexit(onClosing);

    /* Free the name. */
    free(name);

    /* Exit the program with no error. */
    return OK;
}

/*
 * Function called when the program is in debug mode.
 */
static void
run_debug_mode(void) {
    printf("--------------------------------\n");
    printf(ANSI_COLOR_BLUE "Running tests ⤵️\n" ANSI_COLOR_RESET);
    /* Run the tests. */
    run_tests();
    printf("--------------------------------\n");
    printf(ANSI_COLOR_GREEN "Tests finished with no errors ✅\n" ANSI_COLOR_RESET);
}

/*
 * Function to determine if the program is running in debug mode.
 * @return TRUE if the program is running in debug mode, FALSE otherwise.
 */
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

/*
 * Function called when the program is closing.
 */
static void
onClosing(void) {
    printf("Closing the game...\n");
    /* Free the board. */
    free_board(&game.board1);
    printf("Game closed.\n");
}
