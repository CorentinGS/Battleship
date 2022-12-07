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


static void onClosing(void);
static int get_debug_mode(void);
static void run_debug_mode(void);
static void free_game(void);
static void free_player(Player* player);

/* Macro to determine if the program is running in debug mode. */
#define IS_DEBUG_MODE (TRUE == get_debug_mode())

/*
 * Main function.
 */
int
main(int argc, char* argv[]) {
    int err;
    int* coords;

    /* If the program is running in debug mode, run the tests. */
    if (IS_DEBUG_MODE) {
        printf("Debug mode is enabled\n");
        run_debug_mode();
        return OK;
    }

    /* Memset the game structure. */
    memset(&game, 0, sizeof(game));

    /* Init the game. */
    err = init_game();
    if (OK != err) {
        return err;
    }

    /* Print the board. */
    display_board_hidden(&game.board2);

    /* Display the board. */
    display_board(&game.board1);

    coords = malloc(sizeof(int) * 2);
    ask_coordinates(coords);

    place_bomb(&game.board1, coords[0], coords[1]);
    if (NULL != coords) {
        free(coords);
    }

    display_board(&game.board1);

    /* Free on exit. */
    atexit(onClosing);

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

static void
free_game(void) {
    free_player(&game.player1);
    free_player(&game.player2);
}

static void
free_player(Player* player) {
    if (NULL != player->name) {
        free(player->name);
    }
}

/*
 * Function called when the program is closing.
 */
static void
onClosing(void) {
    printf("Closing the game...\n");
    /* Free the board. */
    free_board(&game.board1);
    free_game();
    printf("Game closed.\n");
}
