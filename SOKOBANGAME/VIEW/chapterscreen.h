#ifndef CHAPTERSCREEN_H
#define CHAPTERSCREEN_H


#include "../GAMEPLAY/GAME_LOGIC/GameStart.h"
#include "../UTILS/include/curses.h"
#include "../GAMEPLAY/GAME_LOGIC/GameStart.h"
#include "../UTILS/include/curses.h"
#include "levelscreen.h"
// #include "temp.h"
#include <stdlib.h>
#include <string.h>

#define NCURSES_MOUSE_VERSION

// Jumlah chapter yang tersedia
#define NUM_CHAPTERS 6

// Struktur untuk button
typedef struct {
    int x, y, width, height;
    char *label;
} Button;

// Fungsi untuk menggambar button dengan border dan label
void draw_btn(Button *btn);

// Fungsi untuk mengecek apakah mouse berada di area button
int isbtnarea(Button *btn, int mouse_x, int mouse_y);

// Fungsi utama untuk menampilkan chapter screen dan menangani interaksi mouse
LevelData* print_chapter_screen();

#endif // CHAPTERSCREEN_H
