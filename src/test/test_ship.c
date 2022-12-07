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
#include "test_ship.h"
#include "../ship.h"
#include "../board.h"

static void test_get_ship_size(void);
static void test_create_ship(void);
static void test_set_ship(void);
static void test_is_ship_destroyed(void);
static void test_hit_ship(void);
static void test_unique_ship_id(void);
static void test_get_ship_at(void);
static void test_move_ship(void);

void
test_ship(void) {
    printf(ANSI_COLOR_YELLOW "➡️ ship functions.....\n" ANSI_COLOR_RESET);
    test_get_ship_size();
    test_create_ship();
    test_set_ship();
    test_is_ship_destroyed();
    test_hit_ship();
    test_unique_ship_id();
    test_get_ship_at();
    test_move_ship();
}

static void
test_get_ship_size(void) {
    printf(ANSI_COLOR_MAGENTA "   ➡️ get_ship_size()  \n" ANSI_COLOR_RESET);
    assert(get_ship_size(SHIP_FRIGATE) == SHIP_FRIGATE_SIZE);
    assert(get_ship_size(SHIP_DESTROYER) == SHIP_DESTROYER_SIZE);
    assert(get_ship_size(SHIP_CRUISER) == SHIP_CRUISER_SIZE);
    assert(get_ship_size(SHIP_CARRIER) == SHIP_CARRIER_SIZE);
    assert(get_ship_size(SHIP_NONE) == 0);
    assert(get_ship_size(99) == 0);
}

static void
test_create_ship(void) {
    Ship* ship;
    printf(ANSI_COLOR_MAGENTA "   ➡️ create_ship()  \n" ANSI_COLOR_RESET);
    ship = create_ship();
    assert(ship != NULL);
    assert(ship->type == SHIP_NONE);
    assert(ship->orientation == ORIENTATION_HORIZONTAL);
    assert(ship->head[0] == 0);
    assert(ship->head[1] == 0);

    if (ship != NULL) {
        free_ship(ship);
    }
}

static void
test_set_ship(void) {
    Ship* ship;
    printf(ANSI_COLOR_MAGENTA "   ➡️ set_ship()  \n" ANSI_COLOR_RESET);
    ship = create_ship();
    assert(ship != NULL);
    assert(ship->type == SHIP_NONE);
    assert(ship->orientation == ORIENTATION_HORIZONTAL);
    assert(ship->head[0] == 0);
    assert(ship->head[1] == 0);

    set_ship(ship, SHIP_FRIGATE, 0, 0, ORIENTATION_HORIZONTAL);
    assert(ship->type == SHIP_FRIGATE);
    assert(ship->orientation == ORIENTATION_HORIZONTAL);
    assert(ship->head[0] == 0);
    assert(ship->head[1] == 0);

    set_ship(ship, SHIP_DESTROYER, 1, 1, ORIENTATION_VERTICAL);
    assert(ship->type == SHIP_DESTROYER);
    assert(ship->orientation == ORIENTATION_VERTICAL);
    assert(ship->head[0] == 1);
    assert(ship->head[1] == 1);

    if (ship != NULL) {
        free_ship(ship);
    }
}

static void
test_is_ship_destroyed(void) {
    Ship* ship;
    Board board;
    init_board(&board);
    printf(ANSI_COLOR_MAGENTA "   ➡️ is_ship_destroyed()  \n" ANSI_COLOR_RESET);
    ship = create_ship();
    assert(ship != NULL);

    set_ship(ship, SHIP_FRIGATE, 0, 0, ORIENTATION_HORIZONTAL);

    set_tile_ship(&board.tiles[0][0], ship);

    assert(is_ship_destroyed(ship, &board) == FALSE);

    set_tile_state(&board.tiles[0][0], TILE_STATE_HIT);

    assert(is_ship_destroyed(ship, &board) == TRUE);

    free_board(&board);
}

static void
test_hit_ship(void) {
    Ship *ship, *ship2;
    Board board;
    init_board(&board);
    printf(ANSI_COLOR_MAGENTA "   ➡️ hit_ship()  \n" ANSI_COLOR_RESET);

    ship = create_ship();
    assert(ship != NULL);
    set_ship(ship, SHIP_FRIGATE, 0, 0, ORIENTATION_HORIZONTAL);
    set_tile_ship(&board.tiles[0][0], ship);
    assert(is_ship_destroyed(ship, &board) == FALSE);
    hit_ship(&board, 0, 0);
    assert(check_ships(&board) == 0);

    add_ship(&board, SHIP_DESTROYER, 0, 0, ORIENTATION_HORIZONTAL);

    ship2 = get_ship_at(&board, 0, 0);
    assert(is_ship_destroyed(ship2, &board) == FALSE);
    hit_ship(&board, 0, 0);

    assert(check_ships(&board) == 1);
    hit_ship(&board, 1, 0);
    assert(check_ships(&board) == 0);

    free_board(&board);
}

static void
test_unique_ship_id(void) {
    Ship *ship1, *ship2;
    printf(ANSI_COLOR_MAGENTA "   ➡️ unique_ship_id()  \n" ANSI_COLOR_RESET);
    ship1 = create_ship();
    ship2 = create_ship();
    assert(ship1->id != ship2->id);
    free_ship(ship1);
    free_ship(ship2);
}

static void
test_get_ship_at(void) {
    Board board;
    init_board(&board);
    printf(ANSI_COLOR_MAGENTA "   ➡️ get_ship_at()  \n" ANSI_COLOR_RESET);
    add_ship(&board, SHIP_FRIGATE, 0, 0, ORIENTATION_HORIZONTAL);
    assert(get_ship_at(&board, 0, 0)->type == SHIP_FRIGATE);
    assert(get_ship_at(&board, 1, 0) == NULL);
    add_ship(&board, SHIP_DESTROYER, 2, 2, ORIENTATION_VERTICAL);
    assert(get_ship_at(&board, 2, 2)->type == SHIP_DESTROYER);
    assert(get_ship_at(&board, 2, 3)->type == SHIP_DESTROYER);
    assert(get_ship_at(&board, 2, 4) == NULL);
    free_board(&board);
}

static void
test_move_ship(void) {
    Board board;
    Ship *ship, *ship2;
    int err;
    init_board(&board);
    printf(ANSI_COLOR_MAGENTA "   ➡️ move_ship()  \n" ANSI_COLOR_RESET);
    add_ship(&board, SHIP_FRIGATE, 0, 0, ORIENTATION_HORIZONTAL);
    ship = get_ship_at(&board, 0, 0);
    move_ship(&board, ship, -1);
    assert(get_ship_at(&board, 0, 0) == NULL);
    assert(get_ship_at(&board, 1, 0)->type == SHIP_FRIGATE);
    move_ship(&board, ship, 1);
    assert(get_ship_at(&board, 1, 0) == NULL);
    assert(get_ship_at(&board, 0, 0)->type == SHIP_FRIGATE);

    add_ship(&board, SHIP_DESTROYER, 2, 2, ORIENTATION_VERTICAL);
    ship2 = get_ship_at(&board, 2, 2);
    err = move_ship(&board, ship2, -1);
    if (OK != err) {
        printf("Error: %d", err);
    }
    display_board(&board);

    assert(get_ship_at(&board, 2, 2) == NULL);
    assert(get_ship_at(&board, 2, 3)->type == SHIP_DESTROYER);
    assert(get_ship_at(&board, 2, 4)->type == SHIP_DESTROYER);

    move_ship(&board, ship2, 1);
    display_board(&board);

    assert(get_ship_at(&board, 2, 4) == NULL);
    assert(get_ship_at(&board, 2, 2)->type == SHIP_DESTROYER);
    assert(get_ship_at(&board, 2, 3)->type == SHIP_DESTROYER);

    display_board(&board);

    free_board(&board);
}
