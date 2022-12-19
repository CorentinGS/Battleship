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

#include "utils.h"
#include "../game.h"

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

GameDirection
input_vector_to_direction(const char* input) {
    switch (input[0]) {
        case 'd':
            return GAME_DIRECTION_DOWN;
        case 'u':
            return GAME_DIRECTION_UP;
        case 'l':
            return GAME_DIRECTION_LEFT;
        case 'r':
            return GAME_DIRECTION_RIGHT;
        default:
            return GAME_DIRECTION_NONE;
    }
}

void
get_random_ai_name(char* name) {
    const char COMPUTER_NAMES[5][MAX_NAME_SIZE] = {"Totoro", "Chihiro", "Haku", "Satsuki", "Kiki"};

    srand(time(NULL));
    strcpy(name, COMPUTER_NAMES[rand() % 2]);
}

void
display_game_mode(GameMode mode) {
    switch (mode) {
        case GAME_MODE_SINGLE:
            printf("You are playing against the computer.\n");
            break;
        case GAME_MODE_MULTI:
            printf("You are playing against another player.\n");
            break;
        default:
            printf("Unknown game mode.\n");
            break;
    }
}

void
display_header(Game* game) {
    printf("========================================\n");
    printf("Battleship\n");
    printf("By: CorentinGS\n");
    printf("LICENCE: BSD-3\n");
    printf("Created: 2022/12/15 by CorentinGS\n");
    printf("========================================\n");
    printf("Welcome to Battleship!\n");
    printf("You are playing against %s.\n", game->player2.name);
    printf("========================================\n");
}
