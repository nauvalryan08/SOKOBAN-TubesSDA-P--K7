#ifndef CHAPTERSCREEN_H
#define CHAPTERSCREEN_H
#define NCURSES_MOUSE_VERSION
#include "chapterscreen.h"
#include "../GAMEPLAY/GAME_LOGIC/GameStart.h"
#include "../UTILS/include/curses.h"
#include "levelscreen.h"

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
  Button chapters[] = {
      {COLS / 4, LINES / 2 - 15, COLS / 2, 4, "Chapter 1"},
      {COLS / 4, LINES / 2 - 10, COLS / 2, 4, "Chapter 2"},
      {COLS / 4, LINES / 2 - 5, COLS / 2, 4, "Chapter 3"},
      {COLS / 4, LINES / 2 , COLS / 2, 4, "Chapter 4"},
      {COLS / 4, LINES / 2 + 5, COLS / 2, 4, "Chapter 5"},
      {COLS / 4, LINES / 2 + 10, COLS / 2, 4, "Chapter 6"},
  };
  int n_chapters = 6;
  int selected = 0; // Track selected chapter

  // Enable keypad for arrow keys
  keypad(stdscr, TRUE);

  int ch;
  MEVENT event;
  while ((ch = getch()) != 27) { // ESC untuk keluar
    // Handle keyboard input
    switch (ch) {
      case KEY_UP:
        selected = (selected > 0) ? selected - 1 : n_chapters - 1;
        break;
      case KEY_DOWN:
        selected = (selected < n_chapters - 1) ? selected + 1 : 0;
        break;
      case '\n':
      case KEY_ENTER:
        // Handle chapter selection
        if (selected >= 0 && selected < n_chapters) {
          selected_level = select_level();
          if (selected_level != NULL) {
            run_level(selected_level);
          }
          return;
        }
        break;
    }

    // Handle mouse input
    if (ch == KEY_MOUSE) {
      if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_CLICKED) {
          for (int i = 0; i < n_chapters; i++) {
            if (isbtnarea(&chapters[i], event.x, event.y)) {
              selected = i; // Update selected when clicking
              selected_level = select_level();
              if (selected_level != NULL) {
                run_level(selected_level);
              }
              return;
            }
          }
        }
      }
    }

    // Clear screen and redraw
    clear();
    
    // Draw instructions
    mvprintw(1, 1, "Klik kiri pada tombol chapter untuk memilih chapter!");
    mvprintw(2, 1, "Gunakan tombol ESC untuk kembali ke menu utama");
    mvprintw(3, 1, "Gunakan tombol panah atas/bawah untuk navigasi");
    mvprintw(4, 1, "Tekan ENTER untuk memilih chapter");

    // Draw all buttons
    for (int i = 0; i < n_chapters; i++) {
      if (i == selected) {
        attron(A_REVERSE); // Highlight selected button
      }
      draw_btn(&chapters[i]);
      if (i == selected) {
        attroff(A_REVERSE);
      }
    }

    refresh();
  }
}

#endif // CHAPTERSCREEN_H
