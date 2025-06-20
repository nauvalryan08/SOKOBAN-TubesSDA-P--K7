#ifndef LOBBYSCREEN_H
#define LOBBYSCREEN_H

#include "../UTILS/include/curses.h"
#include "viewtoolkit.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MENU_ITEMS 5
#define ANIMATION_FRAMES 4

typedef struct {
  int x, y;
  int direction;
} Animation;

// Fungsi untuk menampilkan layar lobby
int show_lobby_screen();
// Fungsi untuk menggambar animasi sokoban
void draw_sokoban_animation(Animation *anim, int frame);
// Fungsi untuk menampilkan menu
int show_menu(int selected, int start_y); // Deklarasi diperbaiki
// Fungsi untuk menampilkan judul sokoban
void print_sokoban_title();

#endif
