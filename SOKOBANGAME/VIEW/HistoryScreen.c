#define NCURSES_MOUSE_VERSION
#include "HistoryScreen.h"

// global state
LevelData* global_selected_level = NULL;

LevelData* print_chapter_screen(const char *username) {
  
  LevelData* selected_level = NULL;

  clear();
  mmask_t old;
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, &old);

  int n_chapters = 6;
  int selected = 0; // Track selected chapter

  // Enable keypad for arrow keys
  keypad(stdscr, TRUE);

  int ch;
  int prev_lines = LINES;
  int prev_cols = COLS;
  MEVENT event;
  while ((ch = getch()) != 27) { // ESC untuk keluar
    Button chapters[] = {
      {COLS / 4, LINES / 2 - 15, COLS / 2, 4, "Tutorial"},
      {COLS / 4, LINES / 2 - 10, COLS / 2, 4, "Chapter 1"},
      {COLS / 4, LINES / 2 - 5, COLS / 2, 4, "Chapter 2"},
      {COLS / 4, LINES / 2 , COLS / 2, 4, "Chapter 3"},
      {COLS / 4, LINES / 2 + 5, COLS / 2, 4, "Chapter 4"},
      {COLS / 4, LINES / 2 + 10, COLS / 2, 4, "Chapter 5"},
    };
    // Handle keyboard input
    
    handle_resize(&prev_lines, &prev_cols);

    switch (ch) {
      //keyboard up
      case KEY_UP:
        selected = (selected > 0) ? selected - 1 : n_chapters - 1;
        break;
      //keyboard down
      case KEY_DOWN:
        selected = (selected < n_chapters - 1) ? selected + 1 : 0;
        break;
      //Highlight level jika di click sekali pada ui
      case KEY_MOUSE:
        if (getmouse(&event) == OK) {
          if (event.bstate & BUTTON1_CLICKED){
            for (int i = 0; i < n_chapters; i++) {
              if (isbtnarea(&chapters[i], event.x, event.y)) {
                    selected = i;
              }
            }
          }
        }
        break;
      // \n agar mencegah newline menjadi input
      case '\n':
      //Untuk memilih level menggunakan enter
      case KEY_ENTER:
        pthread_t enterSound;
        if (selected >= 0 && selected <= n_chapters) {
          // Panggil fungsi level selection yang sesuai dengan chapter yang dipilih
          switch(selected) {
            case 0: // Tutorial
              pthread_create(&enterSound, NULL, playEnterSound, NULL);
              selected_level = select_level_tutorial();
              break;
            case 1: // Chapter 1
              pthread_create(&enterSound, NULL, playEnterSound, NULL);
              selected_level = select_level_chapter1();
              break;
            case 2: // Chapter 2
              pthread_create(&enterSound, NULL, playEnterSound, NULL);
              selected_level = select_level_chapter2();
              break;
            case 3: // Chapter 3
              pthread_create(&enterSound, NULL, playEnterSound, NULL);
              selected_level = select_level_chapter3();
              break;
            case 4: // Chapter 4
              pthread_create(&enterSound, NULL, playEnterSound, NULL);
              selected_level = select_level_chapter4();
              break;
            case 5: // Chapter 5
              pthread_create(&enterSound, NULL, playEnterSound, NULL);
              selected_level = select_level_chapter5();
              break;
          }
          
          if (selected_level != NULL) {
            run_level(selected_level, &ChapterTrees[selected], username);
            return selected_level;
          }
          pthread_join(enterSound, NULL);
          return NULL;
        }
        break;
      case KEY_RESIZE:
        resize_term(0,0);
        break;
    }

    //Pengecekan Input mouse double click untuk pemilihan level
    if (ch == KEY_MOUSE) {
      if (getmouse(&event) == OK) {
        if (event.bstate & BUTTON1_DOUBLE_CLICKED) {
          for (int i = 0; i < n_chapters; i++) {
            if (isbtnarea(&chapters[i], event.x, event.y)) {
              selected = i;
                            // Panggil fungsi level selection yang sesuai dengan chapter yang dipilih
              switch(selected) {
                case 0:
                  selected_level = select_level_tutorial();
                  break;
                case 1:
                  selected_level = select_level_chapter1();
                  break;
                case 2:
                  selected_level = select_level_chapter2();
                  break;
                case 3:
                  selected_level = select_level_chapter3();
                  break;
                case 4:
                  selected_level = select_level_chapter4();
                  break;
                case 5:
                  selected_level = select_level_chapter5();
                  break;
              }
              if (selected_level != NULL) {
                run_level(selected_level, &ChapterTrees[selected-1], username);
                return selected_level;
              }
              return NULL;
            }
          }
        }
      }
    }

    clear();
    
    // Instruksi
    mvprintw(1, 1, "Klik kiri pada tombol chapter untuk memilih chapter!");
    mvprintw(2, 1, "Atau gunakan tombol panah atas/bawah untuk navigasi");
    mvprintw(3, 1, "Gunakan tombol ESC untuk kembali ke menu utama");
    mvprintw(4, 1, "Tekan ENTER untuk memilih chapter");

    // menampilkan button
    for (int i = 0; i < n_chapters; i++) {
      if (i == selected) {
        attron(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
      }
      draw_btn(&chapters[i]);
      if (i == selected) {
        attroff(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
      }
    }

    refresh();
  }
}
