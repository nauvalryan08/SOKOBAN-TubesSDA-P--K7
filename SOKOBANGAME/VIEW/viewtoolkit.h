#ifndef VIEWTK_H
#define VIEWTK_H
#include "../UTILS/include/curses.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
  int x, y, width, height;
  char *label;
} Button;

void draw_btn(Button *btn);
int isbtnarea(Button *btn, int mouse_x, int mouse_y);
void handle_resize(int *prev_lines, int *prev_cols);

// New utility functions for drawing UI elements
void draw_box(int x, int y, int width, int height);
void draw_centered_text(int y, int x, int width, const char* text);
void draw_horizontal_line(int y, int x, int width);

#endif