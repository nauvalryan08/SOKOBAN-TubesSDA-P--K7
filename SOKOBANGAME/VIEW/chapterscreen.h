#ifndef CHAPTERSCREEN_H
#define CHAPTERSCREEN_H
#define NCURSES_MOUSE_VERSION

#include "../GAMEPLAY/GAME_LOGIC/GameStart.h"
#include "../UTILS/include/curses.h"
#include "levelscreen.h"
#include "viewtoolkit.h"
// #include "temp.h"
#include <stdlib.h>
#include <string.h>


// Jumlah chapter yang tersedia
#define NUM_CHAPTERS 6

// Fungsi utama untuk menampilkan chapter screen dan menangani interaksi mouse
LevelData* print_chapter_screen();

#endif // CHAPTERSCREEN_H
