###############################################################################
#  Copyright (c) 2022.                                                        #
#                                                                             #
#                                                                             #
#  Battleship                             ______   _______      _______.      #
#  CMakeLists.txt                        /      | /  _____|    /       |      #
#                                       |  ,----'|  |  __     |   (----`      #
#  By: CorentinGS                       |  |     |  | |_ |     \   \          #
#  <c.giaufersaubert@outlook.com>       |  `----.|  |__| | .----)   |         #
#                                        \______| \______| |_______/  (_/ -/  #
#  LICENCE: BSD-3                                                      /  /   #
#  Created: 2022/11/7 by CorentinGS                                           #
#                                                                             #
###############################################################################

cmake_minimum_required(VERSION 3.23)
project(Battleship C)

set(CMAKE_C_STANDARD 90)

add_executable(Battleship
        src/main.c src/player.c src/player.h src/utils/const.h src/struct.h src/utils/config.h src/board.c src/board.h src/tile.c src/tile.h src/common.h src/main.h src/ship.c src/ship.h src/test/test_handler.c src/test/test_handler.h src/test/test_board.c src/test/test_board.h src/test/test_ship.c src/test/test_ship.h src/bomb.c src/bomb.h src/io.c src/io.h src/utils/utils.c src/utils/utils.h src/init.c src/init.h src/game.c src/game.h src/libs/stdprof.c src/libs/stdprof.h src/utils/parser.c src/utils/parser.h src/ai.c src/ai.h src/test/test_io.c src/test/test_io.h src/libs/linked_list.c src/libs/linked_list.h src/test/test_parser.c src/test/test_parser.h)
