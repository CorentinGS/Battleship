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

/*
 * This function is used to get the player's name from stdin.
 * @param name The string where the name will be stored.
 * @param size The size of the string.
 */
int
get_player_name(char* name, const int size) {
    char* error;
    printf("Please enter your name: ");
    /* We use fgets instead of scanf because it is safer. */
    error = fgets(name, size, stdin);
    if (NULL == error) {
        return ERROR;
    }

    return OK;
}

Player*
create_player(void) {
    Player* player;

    /* Allocate memory for the player. */
    player = malloc_prof(sizeof(*player));

    player->name = malloc_prof(sizeof(player->name) * MAX_NAME_SIZE);
    player->type = PLAYER_TYPE_HUMAN;
    return player;
}
