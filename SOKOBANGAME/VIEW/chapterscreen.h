#ifndef CHAPTERSCREEN_H
#define CHAPTERSCREEN_H

#include "../GAMEPLAY/GAME_LOGIC/GameStart.h"
#include "../UTILS/include/curses.h"
#include "levelscreen.h"
#include <stdlib.h>
#include <string.h>

// Jumlah chapter yang tersedia
#define NUM_CHAPTERS 3

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
void print_chapter_screen(LevelData *selected_level);

#endif // CHAPTERSCREEN_H
