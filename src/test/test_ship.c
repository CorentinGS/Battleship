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

static void test_get_ship_size(void);

void
test_ship(void) {
    printf(ANSI_COLOR_YELLOW "➡️ ship functions.....\n" ANSI_COLOR_RESET);
    test_get_ship_size();
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
