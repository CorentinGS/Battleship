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
#include "game.h"
#include "utils/parser.h"

static void onClosing(void);
static int get_debug_mode(void);
static void run_debug_mode(void);
static void free_prof_game(void);
static void free_prof_player(Player* player);
static int no_op(void);

/* Macro to determine if the program is running in debug mode. */
#define IS_DEBUG_MODE (TRUE == get_debug_mode())

/*
 * Main function.
 */
int
main(int argc, char* argv[]) {
    int err;
    int* coords;
    char* filename;

    /* If the program is running in debug mode, run the tests. */
    if (IS_DEBUG_MODE) {
        printf("Debug mode is enabled\n");
        run_debug_mode();
        return OK;
    }

    /* Memset the game structure. */
    memset(&game, 0, sizeof(game));

    /* free_prof on exit.   */
    atexit(onClosing);

    /* Check if the program has been called with a filename. */
    if (argc < 2) {
        err = no_op();
        if (OK != err) {
            printf("Error: %d\n", err);
        }
    }

    /* Get the filename. */
    filename = argv[1];
    /* Process the file. */
    err = process_file(filename);
    if (OK != err) {
        printf("Error: %d\n", err);
    }

    /* Exit the program with no error. */
    return OK;
}

static int
no_op(void) {
    int err;
    /* Init the game. */
    err = init_game();
    if (OK != err) {
        return err;
    }

    game_loop(&game);

    return OK;
}

/*
 * Function called when the program is in debug mode.
 */
static void
run_debug_mode(void) {
    game.width = BOARD_WIDTH;
    game.height = BOARD_HEIGHT;
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
free_prof_game(void) {
    free_prof_player(&game.player1);
    free_prof_player(&game.player2);
}

static void
free_prof_player(Player* player) {
    if (NULL != player->name) {
        free_prof(player->name);
    }
}

/*
 * Function called when the program is closing.
 */
static void
onClosing(void) {
    printf("Closing the game...\n");
    /* free_prof the board. */
    free_prof_board(&game.board1);
    free_prof_game();
    printf("Game closed.\n");
}
