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
#include "test_parser.h"
#include "../utils/parser.h"

static void test_open_file(void);
static void test_close_file(void);
static void test_read_file_line_by_line(void);
static void garbage_line(char* line);

void
test_parser(void) {
    test_open_file();
    test_close_file();
    test_read_file_line_by_line();
}

static void
test_open_file(void) {
    FILE* file;

    printf(ANSI_COLOR_MAGENTA "   ➡️ open_file()  \n" ANSI_COLOR_RESET);
    file = open_file("./src/scenarios/format3.txt");
    if (NULL == file) {
        printf(ANSI_COLOR_RED "   ❌ Cannot open file.  \n" ANSI_COLOR_RESET);
    }

    fclose(file);
}

static void
test_close_file(void) {
    int err;
    FILE* file;
    printf(ANSI_COLOR_MAGENTA "   ➡️ close_file()  \n" ANSI_COLOR_RESET);

    file = open_file("./src/scenarios/format3.txt");
    err = close_file(file);
    if (OK != err) {
        printf(ANSI_COLOR_RED "   ❌ Cannot close file.  \n" ANSI_COLOR_RESET);
    }
}

static void
test_read_file_line_by_line(void) {
    FILE* file;
    char* buffer;
    int err;

    printf(ANSI_COLOR_MAGENTA "   ➡️ read_file_line_by_line()  \n" ANSI_COLOR_RESET);
    file = open_file("./src/scenarios/format3.txt");
    buffer = malloc_prof(FILE_BUFFER_SIZE * sizeof(*buffer));
    err = read_file_line_by_line(file, buffer, garbage_line);
    if (OK != err) {
        printf(ANSI_COLOR_RED "   ❌ Cannot read file.  \n" ANSI_COLOR_RESET);
    }
    printf("%s", buffer);
    free_prof(buffer);
    fclose(file);
}

static void
garbage_line(char* line) {
    /* check if line is valid or freed */
    assert(line != NULL);
}
