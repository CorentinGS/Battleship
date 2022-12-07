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

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "const.h"

int
is_in_array(const int* array, int size, int value) {
    int i;
    for (i = 0; i < size; i++) {
        if (array[i] == value) {
            return TRUE;
        }
    }
    return FALSE;
}

void
get_random_ai_name(char* name) {
    const char COMPUTER_NAMES[2][MAX_NAME_SIZE] = {"Totoro", "TOTO"};

    srand(time(NULL));
    strcpy(name, COMPUTER_NAMES[rand() % 2]);
}
