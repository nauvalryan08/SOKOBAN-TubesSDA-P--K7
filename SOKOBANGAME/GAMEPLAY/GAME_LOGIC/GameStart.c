#include "GameStart.h"

//==========================================================//
//== Method untuk menjalankan Level berdasarkan Parameter ==//
//==========================================================//
/* {Sopian} */

volatile int global_timer = 0;   // waktu dalam detik
volatile int timer_running = 1;  // flag kontrol

// thread Time
void* timer_thread(void *arg) {
    while (timer_running) {
        sleep(1);
        global_timer++;
    }
    return NULL;
}

void start_level (RoomLayout *room, LevelData *level, ChapterData * current_chapter, const char *username) {
    clear();

    pthread_t startSound;
    pthread_t enterSound;

    pthread_create(&startSound, NULL, playStartGameSound, NULL);
    pthread_create(&enterSound, NULL, playStartGameSound, NULL);
    pthread_detach(startSound);
    pthread_detach(enterSound);

    // ==> threading time
    global_timer = 0;
    timer_running = 1;
    pthread_t tid;
    pthread_create(&tid, NULL, timer_thread, NULL);
    //=======>

    nodelay(stdscr, FALSE);
    keypad(stdscr, TRUE);
    curs_set(0);

    // --- > Inisiasi Area <---- //


    Stack StackUndo;
    Queue replayQueue;
    int keyOutput = 0, tempOutput;
    int prev_lines = LINES;
    int prev_cols = COLS;
    ScoreData scoreData = {0};

    Button btn = {2, LINES - 10, 20, 4, "Exit"};

    const char **map = level->map;
    room->finish.is_activated = false;

    // ====> INISIASI UNTUK STACK DAN QUEUE
    stack_init(&StackUndo);
    initQueue(&replayQueue);
    //------------------------------------

    //-----------------------------//

    // --> Parsing data untuk RoomLayout <-- //

    // Cek apakah ada save untuk level ini
    SaveState loaded;
    int ID_data = (int)time(NULL);;

    if (load_game_state(username, level->level_id, &loaded)) {
        if (ask_continue_save()) {
            *room = loaded.room;
            ID_data = loaded.ID_data;
            // Coba load dari file sementara dulu
            if (!load_temp_play_data(username, ID_data, &scoreData, &replayQueue)) {
                load_play_data_by_id(username, ID_data, &scoreData, &replayQueue);
            }
            global_timer = scoreData.time;      //Melnautkan waktu pada state save
            // remove data dari file
            remove_game_state_entry(username, level->level_id, ID_data);
            remove_temp_play_data_entry(username, ID_data, level->level_id);
        } else {
            parse_room(room, level->map);
            remove_game_state_entry(username, level->level_id, ID_data);
            remove_temp_play_data_entry(username, ID_data, level->level_id);

        }
    } else {
        parse_room(room, level->map);
    }
    //-----------------------------//

    nodelay(stdscr, TRUE);

    //simpan data roomLayout ke undo stack
    save_state(&StackUndo, room);


    //===================//
    // --> GAME LOOP <-- //
    //===================//
    getch();
    while (1) {
        prev_lines = LINES;
        prev_cols = COLS;

        handle_resize(&prev_lines, &prev_cols);

        scoreData.time = global_timer;

        // ===>  update status objek 
        update_box_activation_status (room);
        update_finish_activation_status (room);
        //------------------

        //===> handle input :
        handle_input (room, map, &StackUndo, &replayQueue, &keyOutput, &btn, username);
        nodelay(stdscr, TRUE);


        if (keyOutput == 27) {      //ESC button
            nodelay(stdscr, FALSE);
            tempOutput = exit_game(room, username, level->level_id, ID_data, &replayQueue, scoreData);
            if (tempOutput == 0) {
                nodelay(stdscr, TRUE);
            } else if (tempOutput == 1) {
                break;
            }
        } else if (keyOutput == 'F') {      //Cheat Button
            nodelay(stdscr, FALSE);
            room->finish.is_activated = true;
        }else if (keyOutput == 1) {
            update_total_move(&scoreData, +1);
        } else if (keyOutput == 'U') {
            update_total_undo(&scoreData, +1);
        } else if (keyOutput == 'R') {
            set_score_data(&scoreData, 0,0,0,0);
            global_timer = 0;
        }
        keyOutput = 0;
        //-----------------

        // ===> print RoomFactory [Menampilkan output tampilan ruangan sesuai data layout]
        print_room (level->level_name, map, room, scoreData, &btn);
        //---------------------------------------------------------------------------

        // ===> Check victory condition [Memeriksa kondisi menang]
        if (is_victory(room)) {
            print_room (level->level_name, map, room, scoreData, &btn);
            scoreData.time = global_timer;
            int new_id_data = game_finished(room, level, current_chapter, &replayQueue, scoreData, username);
            ID_data = new_id_data;
            break; // Keluar dari loop game
        }
        //-------------------------------------------------
    }

    //bersihkan chace pada stack
    nodelay(stdscr, FALSE);

    if (timer_running) {
        timer_running = 0;
        pthread_join(tid,NULL);
        scoreData.time = global_timer; // sementara (jaga2)
    }

    stack_clear(&StackUndo);
    clearQueue(&replayQueue);
}

// ===> Game finish logic (Save Data, input option)
int game_finished(RoomLayout *room, LevelData *level, ChapterData *current_chapter, Queue *replayQueue, ScoreData scoreData, const char *username) {
    int prev_lines = LINES;
    int prev_cols = COLS;
    Queue q;
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    pthread_t winSound, enterSound;
    pthread_create(&winSound, NULL, playWinSound, NULL);
    pthread_join(winSound, NULL);

    calculate_score(&scoreData, room->box_count);

    char *msg1 = "^_^ CONGRATULATION. YOU WIN! ^_^";
    char *msg2 = "1. Replay  | 2. Next Stage  | 3. Quit";
    Txtbox text[] = {
        {COLS / 2 - strlen(msg1)/2 - 2, LINES / 2 - 4, strlen(msg1) + 4, 2, msg1, "BOLD"},
        {COLS / 2 - strlen(msg1)/2 - 4, LINES / 2 - 1, strlen(msg2) + 4, 2, msg2, "BOLD"}
    };

    level->is_finished = true;
    Ptree node = findTreeNode(current_chapter->ChapterTree, (void*)level, compareDataID);
    if (node != NULL) {
        unlock_child_if_parent_finished(node);
    }

    LevelID current_level_id = level_id_from_string(level->level_id);
    update_player_progress(username, current_level_id);

    // === Simpan ke PLAYDATA ===
    int data_id = (int)time(NULL);
    save_data_to_database(username, level->level_id, data_id, scoreData, replayQueue);

    char dataIDStr[64];
    sprintf(dataIDStr, "%d", data_id);

    int ch;
    while (1) {
        handle_resize(&prev_lines, &prev_cols);

        draw_txtbox(&text[0]);
        draw_txtbox(&text[1]);

        char scoreMsg[64];
        sprintf(scoreMsg, "Final Score: %d", scoreData.score);
        mvprintw((LINES / 2 - 1) + 3, COLS / 2 - (int)strlen(scoreMsg) / 2, "%s", scoreMsg);
        refresh();

        ch = getch();
        if (ch == '1') {
            initReplayQueue(&q);
            if (loadReplayRecord(&q, username, dataIDStr)) {
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                pthread_join(enterSound, NULL);
                playReplay(room, *level, &q);
            } else {
                mvprintw(LINES / 2 + 3, COLS / 2 - 14, "Replay data not found!");
                getch();
            }
            clearQueue(&q);
        } else if (ch == '2') {
            clear();
            print_chapter_screen(username);
            refresh();
            break;
        } else if (ch == '3' || ch == 27) {
            clear();
            refresh();
            break;
        }
    }

    updateAllChapterStatus();
    unlockNextChapter();

    return data_id;
}



//===> Exiting Game (save state or no)

int exit_game(RoomLayout *room, const char *username, const char *ID_level, int ID_data, Queue *replayQueue, ScoreData scoreData) {
    Boolean result = validate_ExitGame();
    if (!result) return 0;

    if (validate_SaveGame()) {
        save_game_state(username, ID_level, ID_data, room);
        save_temp_play_data(username, ID_level, ID_data, scoreData, replayQueue);
        showMsg_SaveSuccess();
        refresh();
    }
    return 1;
}


//====> validator apakah ingin load game state

bool ask_continue_save() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    const char *msg = "Are you want to continue the previous progress? (y/n)";
    clear();
    attron(COLOR_PAIR(9) | A_BOLD);
    mvprintw(max_y / 2, (max_x - strlen(msg)) / 2, "%s", msg);
    attroff(COLOR_PAIR(9) | A_BOLD);
    refresh();

    char ch = getch();
    ch = tolower(ch);
    if (ch == 'y') {
        return 1;
    } else if (ch == 'n') {
        return 0;
    }
}

