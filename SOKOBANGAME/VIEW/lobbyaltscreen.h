#ifndef ALTLOBBY_H
#define ALTLOBBY_H

#include "viewtoolkit.h"
#include "../UTILS/include/curses.h"
#include "../UTILS/sound/soundmanager.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int x, y;
  int direction;
} Anim;

// Fungsi untuk menampilkan judul alternatif
void print_alt_title();
// Fungsi untuk menampilkan menu alternatif
int show_alt_menu(int selected, int items, Button *btnset);
// Fungsi untuk menampilkan lobby alternatif
int show_alt_lobby(const char * username);
#endif