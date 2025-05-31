#include "sokoban.h"
#include "VIEW/lobbyscreen.h"

int main() {

    setlocale(LC_ALL, "");

    initscr();
    
    // Inisialisasi warna
    start_color();
<<<<<<< Updated upstream
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
=======
    init_pair(1, COLOR_CYAN, COLOR_BLACK);   // Warna judul
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);  // Warna animasi
    init_pair(3, COLOR_GREEN, COLOR_BLACK);   // Warna menu
    
    // Warna tambahan untuk game
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_BLACK);
>>>>>>> Stashed changes

    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(0);

<<<<<<< Updated upstream
    RoomLayout room;
    start_level(&room, Level_1c4_map, Level_1c4);
=======
    // Tampilkan lobby screen dan ambil pilihan user
    int menu_choice = show_lobby_screen();
    
    // Handle pilihan menu
    switch (menu_choice) {
        case 0: // Play Game
        {
            RoomLayout room;
            Level_1c2(&room);

            while (1) {
                update_box_activation_status(&room);
                print_room(Level_1c2_map, &room);

                if (is_victory(&room)) {
                    clear();
                    int max_y, max_x;
                    getmaxyx(stdscr, max_y, max_x);

                    const char *msg1 = "🎉 KAMU MENANG 🎉";
                    const char *msg2 = "Tekan ENTER untuk lanjut...";

                    mvprintw(max_y / 2 - 1, (max_x - strlen(msg1)) / 2, "%s", msg1);
                    mvprintw(max_y / 2 + 1, (max_x - strlen(msg2)) / 2, "%s", msg2);
                    refresh();

                    int ch;
                    do {
                        ch = getch();
                    } while (ch != 10 && ch != KEY_ENTER);
                    
                    break;
                }
                handle_input(&room, Level_1c2_map);
            }
            break;
        }
        case 1: // History
            // Implementasi fitur history
            break;
        case 4: // Quit Game
            endwin();
            return 0;
    }
>>>>>>> Stashed changes

    endwin();
    return 0;
}