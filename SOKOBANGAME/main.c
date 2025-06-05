#include "sokoban.h"
#include "VIEW/lobbyscreen.h"
#include "VIEW/tutorial.h"

int main() {

    setlocale(LC_ALL, "");

    initscr();
    
    // Inisialisasi warna
    start_color();

    init_pair(1, COLOR_CYAN, COLOR_BLACK);   // Warna judul
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);  // Warna animasi
    init_pair(3, COLOR_GREEN, COLOR_BLACK);   // Warna menu
    
    // Warna tambahan untuk game
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_BLACK);

    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(0);

    int menu_choice;
    RoomLayout room;

    while (1) {
        menu_choice = show_lobby_screen();

        if (menu_choice == 4) {
            break;
        }

        switch (menu_choice) {
            case 0:
                start_level(&room, Level_1c3_map, Level_1c3);
                break;
            case 1:
                // show_history_screen();
                break;
            case 2:
                // show_leaderboard_screen();
                break;
            case 3:
                show_tutorial_screen();
                break;
        }
    }

    endwin();
    return 0;
}