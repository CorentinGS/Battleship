/******************************************************************************
 * Copyright (c) 2022.                                                        *
 *                                                                            *
 *                                                                            *
 * Battleship                             ______   _______      _______.      *
 * player.c                              /      | /  _____|    /       |      *
 *                                      |  ,----'|  |  __     |   (----`      *
 * By: CorentinGS                       |  |     |  | |_ |     \   \          *
 * <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         *
 *                                       \______| \______| |_______/  (_/ -/  *
 * LICENCE: BSD-3                                                      /  /   *
 * Created: 2022/11/7 by CorentinGS                                           *
 *                                                                            *
 ******************************************************************************/

#include "player.h"
#include <stdio.h>

/*
 * This function is used to get the player's name from stdin.
 * @param name The string where the name will be stored.
 * @param size The size of the string.
 */
void get_player_name(char *name, const int size) {
        printf("Please enter your name: ");
        // We use fgets to read the name from stdin.
        fgets(name, size, stdin);
}

