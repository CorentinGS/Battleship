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

static void set_board_size(char* size);
static void player_action(char* action);

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
    else if (strcmp(token, "J1") == 0 || strcmp(token, "J2") == 0) {
        token = strtok(NULL, " ");
        player_action(token);
    }
}

static void
player_action(char* action) {
    ;
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
    SET_BOARD_WIDTH(width);
    SET_BOARD_HEIGHT(height);
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
read_file_line_by_line(FILE* file, char* buffer, void (*process_line)(char*)) {
    while (NULL != fgets(buffer, FILE_BUFFER_SIZE, file)) {
        process_line(buffer);
    }
    return OK;
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
