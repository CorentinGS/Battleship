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
static void get_input_action(char* input);
static void get_input_vector(char* input);

void
ask_coordinates(int* coordinates) {
    char* input;

    input = malloc_prof(sizeof(*input) * MAX_INPUT_SIZE);
    get_input_coords(input);
    convert_input_to_coordinates(input, coordinates);
    free_prof(input);
}

int
ask_action(void) {
    char* input;
    int action;

    input = malloc_prof(sizeof(*input) * 3);
    get_input_action(input);
    /* safe conversion because we know that the input is a number */
    action = (int)strtol(input, NULL, 10);

    free_prof(input);

    return action;
}

GameDirection
ask_move_vector(void) {
    char* input;
    GameDirection direction;

    input = malloc_prof(sizeof(*input) * 3);

    get_input_vector(input);

    /* convert to direction */
    direction = input_vector_to_direction(input);
    if (GAME_DIRECTION_NONE == direction) {
        /* if the input is not a valid direction, ask again */
        printf("Invalid direction, please try again.\n");
        direction = ask_move_vector();
    }

    free_prof(input);

    return direction;
}

static void
get_input_vector(char* input) {
    printf("Enter the vector of the move (0=forward, 1=backward): ");
    scanf("%s", input);

    if (strlen(input) != 1) {
        printf("Invalid input, please try again.\n");
        get_input_vector(input);
    }

    if (input[0] != '0' && input[0] != '1') {
        printf("Invalid input, please try again.\n");
        get_input_vector(input);
    }

    CLEAR_BUFFER();
}

static void
get_input_action(char* input) {
    printf("What do you want to do? (0: shoot, 1: move a ship) ");
    /* TODO: use fgets instead of scanf */
    scanf("%s", input);

    if (strcmp(input, "0") != 0 && strcmp(input, "1") != 0) {
        printf("Invalid input. Please try again.\n");
        get_input_action(input);
    }

    /* clear the buffer */
    CLEAR_BUFFER();
}

static void
get_input_coords(char* input) {
    printf("Enter coordinates: ");

    fgets(input, MAX_INPUT_SIZE, stdin);
    /* clear the buffer */
    CLEAR_BUFFER();

    if (input[0] < 'A' || input[0] > 'A' + get_board_width() - 1 || input[1] < '1'
        || input[1] > '1' + get_board_height() - 1) {
        printf("Invalid input. Please enter a valid input.\n");
        get_input_coords(input);
    }

    /* input is of the form "A1" */
    /* check if input is valid */
    /* if not, ask again */
    /* Max letter is 'A' + WIDTH - 1 */
    /* Max number is '1' + HEIGHT - 1 */
    /* number is the second & third character */
    if (input[0] < 'A' || input[0] > 'A' + get_board_width() - 1 || input[1] < '1' || input[1] > '9') {
        printf("Invalid input. Please enter a valid input.\n");
        get_input_coords(input);
    }
}

static void
convert_input_to_coordinates(const char* input, int* coordinates) {
    coordinates[0] = input[0] - 'A';
    /* if input[2] is a number, then copy it to input[1] */
    coordinates[1] = input[1] - '1';

    /* if input[2] is a number, then add it to coordinates[1] */
    if (input[2] >= '0' && input[2] <= '9') {
        coordinates[1] = (coordinates[1] + 1) * 10 + (input[2] - '1');
    }
}
