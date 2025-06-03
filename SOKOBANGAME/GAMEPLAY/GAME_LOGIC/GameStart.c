#include "GameStart.h"

//==========================================================//
//== Method untuk menjalankan Level berdasarkan Parameter ==//
//==========================================================//
/* {Sopian} */

void start_level (RoomLayout *room, const char **map) {

    Stack StackUndo;
    int keyOutput = 0;
    int prev_lines = LINES;
    int prev_cols = COLS;

    stack_init(&StackUndo);

    parse_room(room, map);      //parsing data berdasarkan map

    //simpan data roomLayout ke undo stack
    save_state(&StackUndo, room);

    while (1) {
        prev_lines = LINES;
        prev_cols = COLS;

        if (is_termresized()) {
            // Update ukuran terminal
            resize_term(0, 0);
            prev_lines = LINES;
            prev_cols = COLS;
            clear(); // Bersihkan layar agar tidak ada artefak lama
        }

        update_box_activation_status (room);
        update_finish_activation_status (room);
        print_room (map, room);

        handle_input (room, map, &StackUndo, &keyOutput);

        if (keyOutput == 27) { // ESC key pressed
            break; // Exit game loop
        }

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
    }

    //bersihkan chace pada stack
    stack_clear(&StackUndo);

}
