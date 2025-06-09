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

void draw_txtbox(Txtbox *textbox){
  // Pengecekan koordinat valid
  if (textbox->y < 0 || textbox->x < 0 || textbox->y + textbox->height >= LINES ||
      textbox->x + textbox->width >= COLS) {
    return;
  }

  // Sudut kiri atas
  mvaddch(textbox->y, textbox->x, ACS_ULCORNER);

  // Sudut kanan atas
  mvaddch(textbox->y, textbox->x + textbox->width, ACS_URCORNER);

  // Sudut kiri bawah
  mvaddch(textbox->y + textbox->height, textbox->x, ACS_LLCORNER);

  // Sudut kanan bawah
  mvaddch(textbox->y + textbox->height, textbox->x + textbox->width, ACS_LRCORNER);

  // Garis horizontal atas dan bawah
  for (int i = 1; i < textbox->width; i++) {
    if (textbox->x + i < COLS) {
      mvaddch(textbox->y, textbox->x + i, ACS_HLINE);
      mvaddch(textbox->y + textbox->height, textbox->x + i, ACS_HLINE);
    }
  }

  // Garis vertikal kiri dan kanan
  for (int i = 1; i < textbox->height; i++) {
    if (textbox->y + i < LINES) {
      mvaddch(textbox->y + i, textbox->x, ACS_VLINE);
      if (textbox->x + textbox->width < COLS) {
        mvaddch(textbox->y + i, textbox->x + textbox->width, ACS_VLINE);
      }
    }
  }

  // Tampilkan label di tengah textbox dengan atribut
  int label_x = textbox->x + (textbox->width - strlen(textbox->label)) / 2;
  int label_y = textbox->y + textbox->height / 2;

  // Apply attributes if specified
  if (textbox->attr != NULL) {
    if (strstr(textbox->attr, "BOLD")) attron(A_BOLD);
    if (strstr(textbox->attr, "REVERSE")) attron(A_REVERSE);
    if (strstr(textbox->attr, "UNDERLINE")) attron(A_UNDERLINE);
    if (strstr(textbox->attr, "BLINK")) attron(A_BLINK);
    if (strstr(textbox->attr, "DIM")) attron(A_DIM);
    if (strstr(textbox->attr, "STANDOUT")) attron(A_STANDOUT);
  }

  mvprintw(label_y, label_x, "%s", textbox->label);

  // Turn off all attributes
  if (textbox->attr != NULL) {
    if (strstr(textbox->attr, "BOLD")) attroff(A_BOLD);
    if (strstr(textbox->attr, "REVERSE")) attroff(A_REVERSE);
    if (strstr(textbox->attr, "UNDERLINE")) attroff(A_UNDERLINE);
    if (strstr(textbox->attr, "BLINK")) attroff(A_BLINK);
    if (strstr(textbox->attr, "DIM")) attroff(A_DIM);
    if (strstr(textbox->attr, "STANDOUT")) attroff(A_STANDOUT);
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