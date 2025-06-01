#ifndef LOBBYSCREEN_H
#define LOBBYSCREEN_H

#include "../UTILS/include/curses.h"

#define MENU_ITEMS 5
#define ANIMATION_FRAMES 4

typedef struct {
  int x, y;
  int direction;
} Animation;

int show_lobby_screen();
void draw_sokoban_animation(Animation *anim, int frame);
int show_menu(int selected, int start_y); // Fixed declaration
void print_sokoban_title();
void draw_box(int y, int x, int height, int width);

#endif
