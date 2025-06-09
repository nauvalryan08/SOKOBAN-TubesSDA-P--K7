#include "viewtoolkit.h"
#include "../UTILS/include/curses.h"

void draw_btn(Button *btn) {
  // Pengecekan koordinat valid
  if (btn->y < 0 || btn->x < 0 || btn->y + btn->height >= LINES ||
      btn->x + btn->width >= COLS) {
    return;
  }

  // Sudut kiri atas
  mvaddch(btn->y, btn->x, ACS_ULCORNER);

  // Sudut kanan atas
  mvaddch(btn->y, btn->x + btn->width, ACS_URCORNER);

  // Sudut kiri bawah
  mvaddch(btn->y + btn->height, btn->x, ACS_LLCORNER);

  // Sudut kanan bawah
  mvaddch(btn->y + btn->height, btn->x + btn->width, ACS_LRCORNER);

  // Garis horizontal atas dan bawah
  for (int i = 1; i < btn->width; i++) {
    if (btn->x + i < COLS) {
      mvaddch(btn->y, btn->x + i, ACS_HLINE);
      mvaddch(btn->y + btn->height, btn->x + i, ACS_HLINE);
    }
  }

  // Garis vertikal kiri dan kanan
  for (int i = 1; i < btn->height; i++) {
    if (btn->y + i < LINES) {
      mvaddch(btn->y + i, btn->x, ACS_VLINE);
      if (btn->x + btn->width < COLS) {
        mvaddch(btn->y + i, btn->x + btn->width, ACS_VLINE);
      }
    }
  }

  // Tampilkan label di tengah button
  int label_x = btn->x + (btn->width - strlen(btn->label)) / 2;
  int label_y = btn->y + btn->height / 2;
  mvprintw(label_y, label_x, "%s", btn->label);
}

int isbtnarea(Button *btn, int mouse_x, int mouse_y) {
  return (mouse_x >= btn->x && mouse_x < btn->x + btn->width &&
          mouse_y >= btn->y && mouse_y < btn->y + btn->height);
}

void handle_resize(int *prev_lines, int *prev_cols){
    if (LINES != *prev_lines || COLS != *prev_cols) {
      resize_term(0, 0);
      *prev_lines = LINES;
      *prev_cols = COLS;
    }
}

void draw_box(int x, int y, int width, int height) {
  // Sudut-sudut
  mvaddch(y, x, ACS_ULCORNER);
  mvaddch(y, x + width, ACS_URCORNER);
  mvaddch(y + height, x, ACS_LLCORNER);
  mvaddch(y + height, x + width, ACS_LRCORNER);

  // Garis horizontal atas dan bawah
  for (int i = 1; i < width; i++) {
    if (x + i < COLS) {
      mvaddch(y, x + i, ACS_HLINE);
      mvaddch(y + height, x + i, ACS_HLINE);
    }
  }

  // Garis vertikal kiri dan kanan
  for (int i = 1; i < height; i++) {
    if (y + i < LINES) {
      mvaddch(y + i, x, ACS_VLINE);
      if (x + width < COLS) {
        mvaddch(y + i, x + width, ACS_VLINE);
      }
    }
  }

  // Isi spasi di dalam box
  for (int i = 1; i < height; i++) {
    for (int j = 1; j < width; j++) {
      if (y + i < LINES && x + j < COLS) {
        mvaddch(y + i, x + j, ' ');
      }
    }
  }
}

void draw_centered_text(int y, int x, int width, const char* text) {
  int text_x = x + (width - strlen(text)) / 2;
  if (text_x >= 0 && y >= 0 && y < LINES) {
    mvprintw(y, text_x, "%s", text);
  }
}

void draw_horizontal_line(int y, int x, int width) {
  for (int i = 0; i < width; i++) {
    if (x + i < COLS && y >= 0 && y < LINES) {
      mvaddch(y, x + i, ACS_HLINE);
    }
  }
}