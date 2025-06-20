#ifndef VIEWTK_H
#define VIEWTK_H
#define MIN_Y 35 // sebelumnya : 47
#define MIN_X 120 // sebelumnya : 197
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

// Jenis koneksi pohon
typedef enum {
    CONNECTION_VERTICAL,
    CONNECTION_HORIZONTAL,
    CONNECTION_DIAGONAL
} ConnectionType;

// Struct untuk properti grid tombol
typedef struct {
    int cols;
    int btn_width;
    int btn_height;
    int h_spacing;
    int v_spacing;
    int start_x;
    int start_y;
} btngridprop;

void draw_btn(Button *btn);
int isbtnarea(Button *btn, int mouse_x, int mouse_y);
void handle_resize(int *prev_lines, int *prev_cols);
void termsize_check();
void draw_box(int x, int y, int width, int height);
void draw_txtbox(Txtbox *textbox);
void draw_centered_text(int y, int x, int width, const char* text);
void draw_horizontal_line(int y, int x, int width);

// Fungsi baru untuk visualisasi pohon
void draw_connection(Button *from, Button *to, ConnectionType type);
void draw_tree_connection(Button *parent, Button *child, ConnectionType type);
void draw_tree_connections(Button *buttons, int *parent_indices, int count);

// Menggambar grid tombol menggunakan struct properti
void draw_button_grid(const char **labels, int n_buttons, int selected, const btngridprop *prop);

#endif