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

#include "parser.h"
#include "../board.h"
#include "../bomb.h"

#define PLAYER_1                 0
#define PLAYER_2                 1

#define GET_OTHER_PLAYER(player) (player == PLAYER_1 ? PLAYER_2 : PLAYER_1)

static void set_board_size(char* size);
static void player_action(char* action, int player);
static Board* get_board(int player);
static int get_line_number(void);
static void increment_line_number(void);

static int line_number = 0;

/*
 * This function is used to process a line.
 */
void
process_line(char* line) {
    char* token;
    /* Get the first token. */
    token = strtok(line, " ");
    /* Check if the token is a comment. */
    if (token[0] == '#') {
        return;
    }
    /* Check if the token is a board size. */
    else if (strcmp(token, "Projet") == 0) {
        token = strtok(NULL, " ");
        set_board_size(token);
    }
    /* Check if the token is a player. */
    else if (strcmp(token, "J1") == 0) {
        /* get the end of the line. */
        token = strtok(NULL, "");
        player_action(token, PLAYER_1);
    } else if (strcmp(token, "J2") == 0) {
        token = strtok(NULL, "");
        player_action(token, PLAYER_2);
    } else {
        display_board(&game.board1);
        display_board(&game.board2);
        return;
    }
}

static void
player_action(char* action, int player) {
    int start_x, start_y, end_x, end_y, size, err;
    Orientation orientation;
    Board* board;
    Ship* ship;
    char* token;
    /* Get the second token. */
    token = strtok(action, " ");
    /* Check if the token is a placement. */
    if (strcmp(token, "P") == 0) {
        token = strtok(NULL, " ");
        /* if format is %d:%d-%d */
        if (sscanf(token, "%d:%d-%d", &start_x, &start_y, &end_y) == 3) {
            size = end_y - start_y + 1;
            orientation = ORIENTATION_VERTICAL;
        } else if (sscanf(token, "%d-%d:%d", &start_x, &end_x, &start_y) == 3) {
            size = end_x - start_x + 1;
            orientation = ORIENTATION_HORIZONTAL;
        } else {
            size = 1;
            orientation = ORIENTATION_HORIZONTAL;
        }
        /* Add the ship to the board. */
        board = get_board(player);
        if (NULL == board) {
            printf("Error: board is NULL");
            return;
        }
        add_ship(board, size, start_x, start_y, orientation);
    }
    /* Check if the token is a shot. */
    else if (strcmp(token, "T") == 0) {
        token = strtok(NULL, " ");
        /* if format is %u:%u */
        if (sscanf(token, "%d:%d", &start_x, &start_y) != 2) {
            printf("Error: invalid shot format");
            return;
        }
        /* Add the shot to the board. */
        board = get_board(GET_OTHER_PLAYER(player));
        if (NULL == board) {
            printf("Error: board is NULL");
            return;
        }
        err = place_bomb(board, start_x, start_y);
        if (err != OK) {
            switch (err) {
                case ERROR_TILE_OUT_OF_BOUNDS:
                    printf("Coordinates out of bounds!\n");
                    break;
                case INFO_BOMB_OVERLAP:
                    printf("You already bombed this place!\n");
                    break;
                default:
                    printf("Unknown error!\n");
                    break;
            }
        }
    } else if (strcmp(token, "H") == 0) {
        /* Move a ship up. */
        board = get_board(player);
        if (NULL == board) {
            printf("Error: board is NULL");
            return;
        }

        token = strtok(NULL, " ");
        if (sscanf(token, "%d:%d", &start_x, &start_y) != 2) {
            printf("Error: invalid shot format");
            return;
        }

        ship = get_ship_at(board, start_x, start_y);
        if (NULL == ship) {
            printf("Error: no ship at this position");
            return;
        }

        err = move_ship(board, ship, GAME_DIRECTION_FORWARD);
        if (err != OK) {
            printf("You can't move this ship here!\n");
            return;
        }
    } else if (strcmp(token, "B") == 0) {
        /* Move a ship down. */
        board = get_board(player);
        if (NULL == board) {
            printf("Error: board is NULL");
            return;
        }

        token = strtok(NULL, " ");
        if (sscanf(token, "%d:%d", &start_x, &start_y) != 2) {
            printf("Error: invalid shot format");
            return;
        }

        ship = get_ship_at(board, start_x, start_y);
        if (NULL == ship) {
            printf("Error: no ship at this position");
            return;
        }

        err = move_ship(board, ship, GAME_DIRECTION_BACKWARD);
        if (err != OK) {
            printf("You can't move this ship here!\n");
            return;
        }
    } else if (strcmp(token, "G") == 0) {
        /* Move a ship left. */
        board = get_board(player);
        if (NULL == board) {
            printf("Error: board is NULL");
            return;
        }

        token = strtok(NULL, " ");
        if (sscanf(token, "%d:%d", &start_x, &start_y) != 2) {
            printf("Error: invalid shot format");
            return;
        }

        ship = get_ship_at(board, start_x, start_y);
        if (NULL == ship) {
            printf("Error: no ship at this position");
            return;
        }

        err = move_ship(board, ship, GAME_DIRECTION_FORWARD);
        if (err != OK) {
            printf("You can't move this ship here!\n");
            return;
        }
    } else if (strcmp(token, "D") == 0) {
        /* Move a ship right. */
        board = get_board(player);
        if (NULL == board) {
            printf("Error: board is NULL");
            return;
        }

        token = strtok(NULL, " ");
        if (sscanf(token, "%d:%d", &start_x, &start_y) != 2) {
            printf("Error: invalid shot format");
            return;
        }

        ship = get_ship_at(board, start_x, start_y);
        if (NULL == ship) {
            printf("Error: no ship at this position");
            return;
        }

        err = move_ship(board, ship, GAME_DIRECTION_BACKWARD);
        if (err != OK) {
            printf("You can't move this ship here!\n");
            return;
        }
    } else {
        printf("Error: invalid action format");
        return;
    }
}

static Board*
get_board(int player) {
    if (PLAYER_1 == player) {
        return &game.board1;
    } else {
        return &game.board2;
    }
}

/*
 * This function is used to set the board size.
 * the size is given as a string.
 * it's using widthxheight format.
 */
static void
set_board_size(char* size) {
    int width, height;
    char* token;
    /* Get the width. */
    token = strtok(size, "x");
    width = (int)strtol(token, NULL, 10);
    /* Get the height. */
    token = strtok(NULL, "x");
    height = (int)strtol(token, NULL, 10);
    /* Set the board size. */
    set_board_width(width);
    set_board_height(height);

    init_board(&game.board1);
    init_board(&game.board2);
}

/*
 * This function is used to open a file.
 */
FILE*
open_file(const char* filename) {
    FILE* file;
    file = fopen(filename, "r");
    return file;
}

/*
 * This function is used to close a file.
 */
int
close_file(FILE* file) {
    if (0 != fclose(file)) {
        return ERROR_CANNOT_CLOSE_FILE;
    }
    return OK;
}

/*
 * This function is used to read a file line by line.
 */
int
read_file_line_by_line(FILE* file, char* buffer, void (*processor)(char*)) {
    while (NULL != fgets(buffer, FILE_BUFFER_SIZE, file)) {
        increment_line_number();
        printf("Processing line: %d: %s\n", get_line_number(), buffer);
        /* check if the line is empty. */
        if (NULL == buffer || strlen(buffer) == 0) {
            continue;
        }
        processor(buffer);
    }
    return OK;
}

static int
get_line_number(void) {
    return line_number;
}

static void
increment_line_number(void) {
    ++line_number;
}

/*
 * This function is used to process a file.
 */
int
process_file(const char* filename) {
    FILE* file;
    char* buffer;
    int status;

    file = NULL;
    buffer = malloc_prof(FILE_BUFFER_SIZE * sizeof(*buffer));
    if (NULL == buffer) {
        return ERROR_CANNOT_ALLOCATE_MEMORY;
    }

    file = open_file(filename);

    read_file_line_by_line(file, buffer, process_line);

    status = close_file(file);
    if (OK != status) {
        return status;
    }

    if (NULL != buffer) {
        free_prof(buffer);
    }

    return OK;
}
