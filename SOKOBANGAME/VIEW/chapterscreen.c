#define NCURSES_MOUSE_VERSION
#include "chapterscreen.h"

// status global
LevelData* global_selected_level = NULL;

// Fungsi utama untuk menampilkan layar pemilihan chapter dan menangani interaksi pengguna (keyboard/mouse)
LevelData* print_chapter_screen(const char *username) {
  
  LevelData* selected_level = NULL;

  clear();
  mmask_t old;
  mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, &old);

  int n_chapters = 6;
  int selected = 0; // Menyimpan chapter yang dipilih

  // Aktifkan keypad untuk tombol panah
  keypad(stdscr, TRUE);

  int ch;
  int prev_lines = LINES;
  int prev_cols = COLS;
  MEVENT event;
  while ((ch = getch()) != 27) { // ESC untuk keluar
    clear(); // Hanya clear sekali di awal loop

    Txtbox title = {COLS/2 - 6, 2, strlen("Chapter") + 4, 2, "Chapter", "REVERSED"};
    Button chapters[] = {
      {COLS / 4, LINES / 2 - 15, COLS / 2, 4, "Tutorial"},
      {COLS / 4, LINES / 2 - 10, COLS / 2, 4, "Chapter 1"},
      {COLS / 4, LINES / 2 - 5, COLS / 2, 4, "Chapter 2"},
      {COLS / 4, LINES / 2 , COLS / 2, 4, "Chapter 3"},
      {COLS / 4, LINES / 2 + 5, COLS / 2, 4, "Chapter 4"},
      {COLS / 4, LINES / 2 + 10, COLS / 2, 4, "Chapter 5"},
    };

    // Penanganan input keyboard
    handle_resize(&prev_lines, &prev_cols);

    pthread_t enterSound;
    pthread_t arrowSound;

    switch (ch) {
      //tombol panah atas
      case KEY_UP:
        pthread_create(&arrowSound, NULL, playArrowSound, NULL);
        selected = (selected > 0) ? selected - 1 : n_chapters - 1;
        break;
      //tombol panah bawah
      case KEY_DOWN:
        pthread_create(&arrowSound, NULL, playArrowSound, NULL);
        selected = (selected < n_chapters - 1) ? selected + 1 : 0;
        break;
      //Highlight level jika di klik sekali pada ui
      case KEY_MOUSE:
        if (getmouse(&event) == OK) {
          if (event.bstate & BUTTON1_CLICKED){
            pthread_create(&enterSound, NULL, playEnterSound, NULL);
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
        
        if (selected >= 0 && selected <= n_chapters) {
          // Panggil fungsi pemilihan level yang sesuai dengan chapter yang dipilih
          switch(selected) {
            case 0: // Tutorial
              pthread_create(&enterSound, NULL, playEnterSound, NULL);
              selected_level = tutorial_screen();
              break;
            case 1: // Chapter 1
              pthread_create(&enterSound, NULL, playEnterSound, NULL);
              selected_level = chapter1_screen();
              break;
            case 2: // Chapter 2
              pthread_create(&enterSound, NULL, playEnterSound, NULL);
              selected_level = chapter2_screen();
              break;
            case 3: // Chapter 3
              pthread_create(&enterSound, NULL, playEnterSound, NULL);
              selected_level = chapter3_screen();
              break;
            case 4: // Chapter 4
              pthread_create(&enterSound, NULL, playEnterSound, NULL);
              selected_level = chapter4_screen();
              break;
            case 5: // Chapter 5
              pthread_create(&enterSound, NULL, playEnterSound, NULL);
              selected_level = chapter5_screen();
              break;
          }
          
          if (selected_level != NULL) {
            run_level(selected_level, &ChapterTrees[selected], username);
            return selected_level;
          }
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
                            // Panggil fungsi pemilihan level yang sesuai dengan chapter yang dipilih
              switch(selected) {
                case 0:
                  pthread_create(&enterSound, NULL, playEnterSound, NULL);
                  selected_level = tutorial_screen();
                  break;
                case 1:
                  pthread_create(&enterSound, NULL, playEnterSound, NULL);
                  selected_level = chapter1_screen();
                  break;
                case 2:
                  pthread_create(&enterSound, NULL, playEnterSound, NULL);
                  selected_level = chapter2_screen();
                  break;
                case 3:
                  pthread_create(&enterSound, NULL, playEnterSound, NULL);
                  selected_level = chapter3_screen();
                  break;
                case 4:
                  pthread_create(&enterSound, NULL, playEnterSound, NULL);
                  selected_level = chapter4_screen();
                  break;
                case 5:
                  pthread_create(&enterSound, NULL, playEnterSound, NULL);
                  selected_level = chapter5_screen();
                  break;
              }
              if (selected_level != NULL) {
                run_level(selected_level, &ChapterTrees[selected], username);
                return selected_level;
              }
              
              return NULL;
            }
          }
        }
      }
    }

    pthread_join(arrowSound, NULL);
    pthread_join(enterSound, NULL);

    // Instruksi
    draw_box(0,0,strlen("Klik kiri pada tombol chapter untuk memilih chapter!") + 2, 5);
    mvprintw(1, 1, "Klik kiri pada tombol chapter untuk memilih chapter!");
    mvprintw(2, 1, "Atau gunakan tombol panah atas/bawah untuk navigasi");
    mvprintw(3, 1, "Gunakan tombol ESC untuk kembali ke menu utama");
    mvprintw(4, 1, "Tekan ENTER untuk memilih chapter");
    draw_txtbox(&title);

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

    refresh(); // Hanya dipanggil sekali di akhir loop
  }
}
