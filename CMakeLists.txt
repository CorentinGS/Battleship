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

set(CMAKE_C_STANDARD 99)

add_executable(Battleship
        src/main.c src/player.c src/player.h src/utils/const.h src/struct.h src/utils/config.h src/board.c src/board.h src/tile.c src/tile.h src/common.h src/main.h)
