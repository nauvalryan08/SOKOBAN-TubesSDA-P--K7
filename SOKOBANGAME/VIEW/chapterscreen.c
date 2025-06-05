#ifndef CHAPTERSCREEN_H
#define CHAPTERSCREEN_H
#define NCURSES_MOUSE_VERSION
#include "../GAMEPLAY/GAME_LOGIC/GameStart.h"
#include "../UTILS/include/curses.h"
#include "levelscreen.h"
#include "chapterscreen.h"

typedef struct {
  int x, y, width, height;
  char *label;
} Button;

void draw_btn(Button *btn) {
  // Pastikan koordinat valid
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

void print_chapter_screen(LevelData *selected_level) {
  clear();
  mmask_t old;
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, &old);

  // Buat button chapter
  Button chapters[] = {{COLS / 2 - 6, LINES / 2 - 4, 12, 3, "Chapter 1"},
                       {COLS / 2 - 6, LINES / 2 + 1, 12, 3, "Chapter 2"},
                       {COLS / 2 - 6, LINES / 2 + 6, 12, 3, "Chapter 3"}};
  int n_chapters = 3;

  // Gambar semua button
  for (int i = 0; i < n_chapters; i++) {
    draw_btn(&chapters[i]);
  }

  mvprintw(1, 1, "Klik kiri pada tombol chapter untuk memilih chapter!");
  mvprintw(2, 1, "Gunakan tombol ESC untuk kembali ke menu utama");
  refresh();

  int ch;
  MEVENT event;
  while ((ch = getch()) != 27) { // ESC untuk keluar
    if (ch == KEY_MOUSE) {
      if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_CLICKED) {
          for (int i = 0; i < n_chapters; i++) {
            if (isbtnarea(&chapters[i], event.x, event.y)) {
              // Highlight button yang diklik
              attron(A_REVERSE);
              draw_btn(&chapters[i]);
              attroff(A_REVERSE);
              refresh();

              if (i == 0) {
                selected_level = select_level();
                if (selected_level != NULL) {
                  run_level(selected_level);
                }
              } else if (i == 1) {
                selected_level = select_level();
                if (selected_level != NULL) {
                  run_level(selected_level);
                }
              } 
              else if (i == 2) {
                selected_level = select_level();
                if (selected_level != NULL) {
                  run_level(selected_level);
                }
              }
                return;
            }
          }
        }
      }
    }
  }
}

#endif // CHAPTERSCREEN_H