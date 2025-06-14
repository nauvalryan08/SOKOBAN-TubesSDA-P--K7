#ifndef VIEWTK_H
#define VIEWTK_H
#define MIN_Y 35 // before : 47
#define MIN_X 120 // before : 197
#include "../UTILS/include/curses.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
  int x, y, width, height;
  char *label;
} Button;

typedef struct {
  int x, y, width, height;
  char *label;
  char *attr;
} Txtbox;

void draw_btn(Button *btn);
int isbtnarea(Button *btn, int mouse_x, int mouse_y);
void handle_resize(int *prev_lines, int *prev_cols);
void termsize_check();
void draw_box(int x, int y, int width, int height);
void draw_txtbox(Txtbox *textbox);
void draw_centered_text(int y, int x, int width, const char* text);
void draw_horizontal_line(int y, int x, int width);

#endif