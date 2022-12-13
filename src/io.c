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

#include "io.h"

static void get_input_coords(char* input);
static void convert_input_to_coordinates(const char* input, int* coordinates);

void
ask_coordinates(int* coordinates) {
    char* input;

    input = malloc_prof(sizeof(*input) * 3);
    get_input_coords(input);
    convert_input_to_coordinates(input, coordinates);
    free_prof(input);
}

static void
get_input_coords(char* input) {
    int ch;
    printf("Enter coordinates: ");

    fgets(input, 3, stdin);
    /* clear the buffer */

    while (((ch = getchar()) != EOF) && (ch != '\n')) {
        ;
    }

    /* input is of the form "A1" */
    /* check if input is valid */
    /* if not, ask again */
    /* Max letter is 'A' + WIDTH - 1 */
    if (input[0] < 'A' || input[0] > 'A' + BOARD_WIDTH - 1 || input[1] < '1' || input[1] > '1' + '9') {
        printf("Invalid input. Please enter a valid input.\n");
        get_input_coords(input);
    }
}

static void
convert_input_to_coordinates(const char* input, int* coordinates) {
    coordinates[0] = input[0] - 'A';
    coordinates[1] = input[1] - '1';
}
