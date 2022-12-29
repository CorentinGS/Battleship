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

#ifndef BATTLESHIP_UTILS_H
#define BATTLESHIP_UTILS_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include "const.h"
#include "../struct.h"

#define CLEAR_BUFFER()                                                                                                 \
    do {                                                                                                               \
        int ch;                                                                                                        \
        while ((ch = getchar()) != EOF && ch != '\n') {}                                                               \
    } while (0)

extern int is_in_array(const int* array, int size, int value);
extern void get_random_ai_name(char* name);
extern void display_game_mode(GameMode mode);
extern void display_header(void);
extern GameDirection input_vector_to_direction(const char* input);
extern int get_board_width(void);
extern int get_board_height(void);
extern void set_board_height(int height);
extern void set_board_width(int width);

#endif
