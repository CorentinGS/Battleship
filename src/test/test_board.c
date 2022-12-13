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

#include <assert.h>
#include "test_board.h"
#include "../board.h"
#include "../ship.h"

static void test_add_ship(void);
static void test_get_ships(void);
static void test_check_ships(void);
static void test_is_in_bounds(void);

void
test_board(void) {
    printf(ANSI_COLOR_YELLOW "➡️ board functions.....\n" ANSI_COLOR_RESET);
    test_add_ship();
    test_get_ships();
    test_check_ships();
    test_is_in_bounds();
}

static void
test_add_ship(void) {
    Board board;
    int i, j, x, err;
    printf(ANSI_COLOR_MAGENTA "   ➡️ add_ship()  \n" ANSI_COLOR_RESET);
    for (x = SHIP_FRIGATE; x <= SHIP_CARRIER; ++x) {
        init_board(&board);
        err = add_ship(&board, x, 0, 0, ORIENTATION_HORIZONTAL);
        assert(err == OK);
        for (i = 0; i < get_ship_size(x); ++i) {
            assert(board.tiles[i][0].state == TILE_STATE_SHIP);
        }
        free_prof_board(&board);
    }
    for (x = SHIP_FRIGATE; x <= SHIP_CARRIER; ++x) {
        init_board(&board);
        err = add_ship(&board, x, 0, 0, ORIENTATION_VERTICAL);
        assert(err == OK);

        for (i = 0; i < get_ship_size(x); ++i) {
            assert(board.tiles[0][i].state == TILE_STATE_SHIP);
        }
        free_prof_board(&board);
    }

    init_board(&board);
    err = add_ship(&board, SHIP_FRIGATE, BOARD_WIDTH, 0, ORIENTATION_HORIZONTAL);
    assert(err == ERROR_SHIP_OUT_OF_BOUNDS);
    err = add_ship(&board, SHIP_FRIGATE, 0, BOARD_HEIGHT, ORIENTATION_VERTICAL);
    assert(err == ERROR_SHIP_OUT_OF_BOUNDS);
    err = add_ship(&board, SHIP_CARRIER, 0, 0, ORIENTATION_VERTICAL);
    assert(err == OK);
    err = add_ship(&board, SHIP_FRIGATE, 0, 2, ORIENTATION_HORIZONTAL);
    assert(err == ERROR_SHIP_OVERLAP);
    err = add_ship(&board, SHIP_CARRIER, 8, 0, ORIENTATION_VERTICAL);
    assert(err == OK);

    free_prof_board(&board);
}

static void
test_get_ships(void) {
    Board board;
    int i, x, err;
    int** ships;
    printf(ANSI_COLOR_MAGENTA "   ➡️ get_ships()  \n" ANSI_COLOR_RESET);
    init_board(&board);
    err = add_ship(&board, SHIP_FRIGATE, 0, 0, ORIENTATION_HORIZONTAL);
    assert(err == OK);
    err = add_ship(&board, SHIP_CARRIER, 2, 3, ORIENTATION_VERTICAL);
    assert(err == OK);
    err = add_ship(&board, SHIP_CRUISER, 1, 9, ORIENTATION_HORIZONTAL);

    ships = malloc_prof(sizeof(int*) * 3);
    for (i = 0; i < 3; ++i) {
        ships[i] = malloc_prof(sizeof(int) * 2);
    }
    x = get_ships(&board, ships);
    assert(x == 3);
    assert(ships[0][0] == 0);
    assert(ships[0][1] == 0);
    assert(ships[1][0] == 1);
    assert(ships[1][1] == 9);
    assert(ships[2][0] == 2);
    assert(ships[2][1] == 3);

    for (i = 0; i < 3; ++i) {
        if (NULL != ships[i]) {
            free_prof(ships[i]);
        }
    }
    if (NULL != ships) {
        free_prof(ships);
    }

    free_prof_board(&board);
}

static void
test_check_ships(void) {
    Board board;
    int i, x, err;
    int** ships;
    printf(ANSI_COLOR_MAGENTA "   ➡️ check_ships()  \n" ANSI_COLOR_RESET);
    init_board(&board);
    err = add_ship(&board, SHIP_FRIGATE, 0, 0, ORIENTATION_HORIZONTAL);
    assert(err == OK);
    err = add_ship(&board, SHIP_CARRIER, 2, 3, ORIENTATION_VERTICAL);
    assert(err == OK);
    err = add_ship(&board, SHIP_CRUISER, 1, 9, ORIENTATION_HORIZONTAL);
    assert(err == OK);

    x = check_ships(&board);
    assert(x == 3);

    hit_ship(&board, 0, 0);
    assert(2 == check_ships(&board));

    hit_ship(&board, 1, 9);
    assert(2 == check_ships(&board));

    hit_ship(&board, 2, 9);
    assert(2 == check_ships(&board));
    hit_ship(&board, 3, 9);
    assert(1 == check_ships(&board));

    free_prof_board(&board);
}

static void
test_is_in_bounds(void) {
    Board board;
    init_board(&board);
    printf(ANSI_COLOR_MAGENTA "   ➡️ is_in_bounds()  \n" ANSI_COLOR_RESET);
    assert(is_in_bounds(0, 0) == OK);
    assert(is_in_bounds(BOARD_WIDTH - 1, BOARD_HEIGHT - 1) == OK);
    assert(is_in_bounds(BOARD_WIDTH, BOARD_HEIGHT) == ERROR_TILE_OUT_OF_BOUNDS);
    assert(is_in_bounds(-1, -1) == ERROR_TILE_OUT_OF_BOUNDS);
    free_prof_board(&board);
}
