#include "GameStart.h"

//==========================================================//
//== Method untuk menjalankan Level berdasarkan Parameter ==//
//==========================================================//
/* {Sopian} */

void start_level (RoomLayout *room, const char **map, InitLevel init_level) {

    Stack StackUndo;
    stack_init(&StackUndo);

    init_level(room);                    // dari level.c

    //simpan data roomLayout ke undo stack
    save_state(&StackUndo, room);

    while (1) {
        update_box_activation_status (room);
        update_finish_activation_status (room);
        print_room (map, room);

        if (is_victory(room)) {
            // Bersihkan layar dulu kalau mau
            clear();

            // Ambil ukuran layar
            int max_y, max_x;
            getmaxyx(stdscr, max_y, max_x);

            const char *msg1 = "^_^ KAMU MENANG! ^_^";
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
        handle_input (room, map, init_level, &StackUndo);

    }

    //bersihkan chace pada stack
    stack_clear(&StackUndo);

}
