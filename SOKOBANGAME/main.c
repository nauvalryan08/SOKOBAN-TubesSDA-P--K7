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


    int menu_choice;
    RoomLayout room;
    LevelData *selected_level;
    Ptree PlayData = initDataHierarki();

    initAllChapters();

    while (menu_choice != 5) {
    // Handle pilihan menu

    menu_choice = show_alt_lobby();

    switch (menu_choice) {
    case 1: // Play Game
        selected_level = print_chapter_screen();
        break;
    case 2: // History
        // Implementasi fitur history
        break;
    case 3 :
        break;
    case 4: // How to play
        show_tutorial_screen();
        break;
    case 5: // Quit Game
        return 0;
        break;
    }
    }

    endwin();
    return 0;
}
