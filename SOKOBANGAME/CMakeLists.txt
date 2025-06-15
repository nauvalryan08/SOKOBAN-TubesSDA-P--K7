cmake_minimum_required(VERSION 3.10)

# Set compiler paths - using environment variables for better portability
if(WIN32)
    set(CMAKE_C_COMPILER gcc)
    set(CMAKE_CXX_COMPILER g++)
endif()

project(SOKOBANGAME)

#add_library(libpdcurses STATIC IMPORTED)
#set_property(TARGET libpdcurses PROPERTY IMPOERTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/UTILS/lib/libpdcurses.a")

set(PDCURSES_LIB "${CMAKE_CURRENT_SOURCE_DIR}/UTILS/lib/libpdcurses.a")
if(EXISTS ${PDCURSES_LIB})
    add_library(pdcurses STATIC IMPORTED)
    set_property(TARGET pdcurses PROPERTY IMPORTED_LOCATION ${PDCURSES_LIB})
endif()

# Collect all source files
file(GLOB_RECURSE SRC
    "VIEW/*.c"
    "STRUCTURES/*.c"
    "GAMEPLAY/ARENA_LOGIC/*.c"
    "GAMEPLAY/GAME_LOGIC/*.c"
    "GAMEPLAY/REPLAY_LOGIC/*.c"
    "DATABASE/*.c"
    "FILEDATA/*.c"
    "UTILS/*.c"
    "UTILS/include/*.c"
    "UTILS/sound/*.c"
    "ASSETS/*.c"
)

# Collect all header files
file(GLOB_RECURSE HFILE
    "*.h"
    "VIEW/*.h"
    "STRUCTURES/*.h"
    "GAMEPLAY/ARENA_LOGIC/*.h"
    "GAMEPLAY/GAME_LOGIC/*.h"
    "GAMEPLAY/REPLAY_LOGIC/*.h"
    "DATABASE/*.h"
    "FILEDATA/*.h"
    "UTILS/include/*.h"
    "UTILS/sound/*.h"
    "ASSETS/*.h"
)

add_executable(SOKOBANGAME main.c ${SRC} ${HFILE})

# Link libraries
if(TARGET pdcurses)
    target_link_libraries(SOKOBANGAME pdcurses)
endif()

# Add winmm library for Windows sound support
if(WIN32)
    target_link_libraries(SOKOBANGAME winmm)
endif()

# Include directories
target_include_directories(SOKOBANGAME PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/UTILS/sound/"
    "${CMAKE_CURRENT_SOURCE_DIR}/UTILS/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/VIEW/"
    "${CMAKE_CURRENT_SOURCE_DIR}/STRUCTURES/"
    "${CMAKE_CURRENT_SOURCE_DIR}/GAMEPLAY/"
    "${CMAKE_CURRENT_SOURCE_DIR}/GAMEPLAY/ARENA_LOGIC/"
    "${CMAKE_CURRENT_SOURCE_DIR}/GAMEPLAY/GAME_LOGIC/"
    "${CMAKE_CURRENT_SOURCE_DIR}/GAMEPLAY/REPLAY_LOGIC/"
    "${CMAKE_CURRENT_SOURCE_DIR}/DATABASE/"
    "${CMAKE_CURRENT_SOURCE_DIR}/FILEDATA/"
    "${CMAKE_CURRENT_SOURCE_DIR}/ASSETS/"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Set C standard
set_property(TARGET SOKOBANGAME PROPERTY C_STANDARD 11)
set_property(TARGET SOKOBANGAME PROPERTY C_STANDARD_REQUIRED ON)
