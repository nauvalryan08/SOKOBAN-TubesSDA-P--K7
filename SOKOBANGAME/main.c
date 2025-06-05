#include "sokoban.h"

int main() {

  setlocale(LC_ALL, "");
  initscr();

  // Inisialisasi warna
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLACK, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);

  

  cbreak();
  noecho();
  curs_set(FALSE);
  keypad(stdscr, TRUE);
  timeout(0);

  // Tampilkan lobby screen dan ambil pilihan user
  int menu_choice;
  RoomLayout room;
  LevelData *selected_level;

  while (menu_choice != 4) {
    // Handle pilihan menu

    menu_choice = show_lobby_screen();

    switch (menu_choice) {
    case 0: // Play Game
      /*{
          selected_level = select_level();
          if (selected_level != NULL) {
              run_level(selected_level);
          }
      }*/
      print_chapter_screen(selected_level);
      break;
    case 1: // History
      // Implementasi fitur history
      break;
    case 4: // Quit Game
      break;
    }
  }

  endwin();
  return 0;
}
