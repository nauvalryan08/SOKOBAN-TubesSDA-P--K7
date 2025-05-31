#include "sokoban.h"

int main() {
    initscr();
    
    //inisiasi warna
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_BLACK);

    cbreak();               //input tanpa ENTER
    noecho();               // Input tanpa melihatkan karakter
    curs_set(FALSE);        //curs_set nonaktif
    keypad(stdscr, TRUE);   //mengaktifkan input ENTER,f1,f11, ARROW, dll
    timeout(0);

    RoomLayout room;
    Level_1c1(&room);                    // dari level.c

    while (1) {
        update_box_activation_status (&room);
        update_finish_activation_status (&room);
        print_room (Level_1c1_map, &room);

        if (is_victory(&room)) {
            // Bersihkan layar dulu kalau mau
            clear();

            // Ambil ukuran layar
            int max_y, max_x;
            getmaxyx(stdscr, max_y, max_x);

            const char *msg1 = "🎉 KAMU MENANG 🎉";
            const char *msg2 = "Tekan ENTER untuk lanjut...";

            // Tampilkan teks di tengah layar
            mvprintw(max_y / 2 - 1, (max_x - strlen(msg1)) / 2, "%s", msg1);
            mvprintw(max_y / 2 + 1, (max_x - strlen(msg2)) / 2, "%s", msg2);

            refresh();

            // Tunggu sampai user tekan ENTER
            int ch;
            do {
                ch = getch();
            } while (ch != 10 && ch != KEY_ENTER);

            break; // Keluar dari loop game
        }
        handle_input (&room, Level_1c1_map);

        // napms(30);
    }

    getch();
    endwin();
    return 0;
}
