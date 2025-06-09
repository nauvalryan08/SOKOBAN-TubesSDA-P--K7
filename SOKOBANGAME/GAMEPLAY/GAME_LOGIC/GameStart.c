#include "GameStart.h"

//==========================================================//
//== Method untuk menjalankan Level berdasarkan Parameter ==//
//==========================================================//
/* {Sopian} */

void start_level (RoomLayout *room, LevelData *level, ChapterData * current_chapter) {

    Stack StackUndo;
    Queue hintQueue;
    int keyOutput = 0;
    int prev_lines = LINES;
    int prev_cols = COLS;

    const char **map = level->map;

    stack_init(&StackUndo);
    initQueue(&hintQueue);

    parse_room(room, map);      //parsing data berdasarkan map

    //simpan data roomLayout ke undo stack
    save_state(&StackUndo, room);

    getch();
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

        room->finish.is_activated = true;
        print_room (level->level_name, map, room);

        handle_input (room, map, &StackUndo, &hintQueue, &keyOutput);

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

            Ptree root = current_chapter->ChapterTree;
            LevelData* LevelTree = (LevelData *)root->data;


            // -- mengubah status finished, dan membuka para child nya
            level->is_finished = true;
            refresh();
            Ptree node = findTreeNode(current_chapter->ChapterTree, (void*)level, compareDataID);
            if (node == NULL) {
               mvprintw(3,25,"Node untuk level %s tidak ditemukan di tree!\n", level->level_name);
            } else {
               unlock_child_if_parent_finished(node);
            }
            //  -- debugging --
            // mvprintw(15,30, "level saat ini %s", level->level_id);
            // mvprintw(16,30,"Level di compare %s", ALL_LEVELS[LEVEL_1C1].level_id);
            // mvprintw(17,30,"Tree saat ini %s", LevelTree->level_name);



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
    clearQueue(&hintQueue);
}
