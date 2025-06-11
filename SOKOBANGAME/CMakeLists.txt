cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_COMPILER C:/MinGW/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/MinGW/bin/gcc.exe)

project(SOKOBANGAME)

#add_library(libpdcurses STATIC IMPORTED)
#set_property(TARGET libpdcurses PROPERTY IMPOERTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/UTILS/lib/libpdcurses.a")

file(GLOB_RECURSE SRC
    "VIEW/*.c"
    "STRUCTURES/*.c"
    "GAMEPLAY/ARENA_LOGIC/*.c"
    "GAMEPLAY/GAME_LOGIC/*.c"
)

file(GLOB_RECURSE HFILE
    "*.h"
    "VIEW/*.h"
    "STRUCTURES/*.h"
    "GAMEPLAY/ARENA_LOGIC/*.h"
    "GAMEPLAY/GAME_LOGIC/*.h"
    "UTILS/include/*.h"
)

add_executable(SOKOBANGAME main.c ${SRC} ${HFILE})

target_link_libraries(SOKOBANGAME "${CMAKE_CURRENT_SOURCE_DIR}/UTILS/lib/libpdcurses.a")
target_include_directories(SOKOBANGAME PRIVATE 
  "${CMAKE_CURRENT_SOURCE_DIR}/UTILS/include/"
  "${CMAKE_CURRENT_SOURCE_DIR}/VIEW/"
  "${CMAKE_CURRENT_SOURCE_DIR}")
