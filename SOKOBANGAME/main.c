#include "sokoban.h"
#include "VIEW/lobbyscreen.h"
#include "VIEW/tutorial.h"

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

    initAllChapters();

    while (menu_choice != 4) {
    // Handle pilihan menu

    menu_choice = show_lobby_screen();

    switch (menu_choice) {
    case 0: // Play Game
        // // run_level(&ALL_LEVELS[LEVEL_2C1]);
        // selected_level= select_level_chapter2();
        // run_level(selected_level);
        selected_level = print_chapter_screen();


        break;
    case 1: // History
        // Implementasi fitur history
        break;
    case 3 :
    
        show_tutorial_screen();
        break;
    case 4: // Quit Game
        break;
    }
    }

    endwin();
    return 0;
}
