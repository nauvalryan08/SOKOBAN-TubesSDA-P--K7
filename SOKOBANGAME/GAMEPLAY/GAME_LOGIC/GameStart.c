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

    pthread_t enterSound;
    pthread_create(&enterSound, NULL, playEnterSound, NULL);
    pthread_detach(enterSound);

    // ==> threading time
    global_timer = 0;
    timer_running = 1;
    pthread_t tid;
    pthread_create(&tid, NULL, timer_thread, NULL);
    //=======>

    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);

    Stack StackUndo;
    Queue replayQueue;
    int keyOutput = 0;
    int prev_lines = LINES;
    int prev_cols = COLS;

    ScoreData scoreData = {0};

    Button btn = {2, LINES - 10, 20, 4, "Exit"};

    const char **map = level->map;
    room->finish.is_activated = false;

    stack_init(&StackUndo);
    initQueue(&replayQueue);

    parse_room(room, map);      //parsing data berdasarkan map

    //simpan data roomLayout ke undo stack
    save_state(&StackUndo, room);

    getch();
    while (1) {
        prev_lines = LINES;
        prev_cols = COLS;

        handle_resize(&prev_lines, &prev_cols);

        scoreData.time = global_timer;

        update_box_activation_status (room);
        update_finish_activation_status (room);

        handle_input (room, map, &StackUndo, &replayQueue, &keyOutput, &btn, username);


        if (keyOutput == 27) { // ESC key pressed
            break; // Exit game loop
        } else if (keyOutput == 'F') {
            room->finish.is_activated = true;
        }

        // print_room (level->level_name, map, room, scoreData, &btn);
        print_room (level->level_name, map, room, scoreData, &btn);


        if (is_victory(room)) {
            print_room (level->level_name, map, room, scoreData, &btn);

            scoreData.time = global_timer;
            game_finished(room, level, current_chapter, &replayQueue, scoreData, username);
            break; // Keluar dari loop game
        }
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

void game_finished(RoomLayout *room, LevelData *level, ChapterData *current_chapter, Queue *replayQueue, ScoreData scoreData, const char *username) {

    int prev_lines = LINES;
    int prev_cols = COLS;

    Queue q;

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    pthread_t winSound; // sound effect
    pthread_create(&winSound, NULL, playWinSound, NULL);
    pthread_join(winSound, NULL);

    const char *msg1 = "^_^ KAMU MENANG! ^_^";
    const char *msg2 = "1. Replay  | 2. Next Stage  | 3. Quit";

    // Unlock level berikutnya
    level->is_finished = true;
    Ptree node = findTreeNode(current_chapter->ChapterTree, (void*)level, compareDataID);
    if (node != NULL) {
        unlock_child_if_parent_finished(node);
    }

    // Simpan replay ke database
    char dataID[64];
    sprintf(dataID, "%s_%ld", level->level_id, time(NULL)); // Format unik ID
    saveDataToDatabase(replayQueue, username, level->level_id, dataID, scoreData);

    // Pilihan pasca menang
    int ch;
    while (1) {
        handle_resize(&prev_lines, &prev_cols);

        attron(COLOR_PAIR(9) | A_BOLD);
        mvprintw(max_y / 2 - 2, (max_x - strlen(msg1)) / 2, "%s", msg1);
        mvprintw(max_y / 2, (max_x - strlen(msg2)) / 2, "%s", msg2);
        attroff(COLOR_PAIR(9) | A_BOLD);

        refresh();

        ch = getch();
        if (ch == '1') {
            // Replay langkah yang baru saja dimainkan
            initReplayQueue(&q);
            if (loadReplayRecord(&q, username, dataID)) {
                playReplay(room, *level, &q);
            } else {
                mvprintw(max_y / 2 + 3, (max_x - 30) / 2, "Replay tidak ditemukan!");
                getch();
            }
            clearQueue(&q);
        } else if (ch == '2') {
            
            continue;
        } else if (ch == '3' || ch == 27) {
            // kembali ke lobby
            break;;
        }
    }
    updateAllChapterStatus();

    unlockNextChapter();
}


//=================================================//
//==                DATABASE ACCESS              ==//
//=================================================//
/* {Sopian} */

void saveDataToDatabase ( Queue *q, const char *username, const char *levelID, const char *dataID, ScoreData scoreData) {

    FILE *fp = fopen(PLAY_DATA_PATH, "a");
    if (!fp) return;

    // Tulis metadata
    fprintf(fp, "%s|%s|%s|%d|%d|%d|%d|",
        username,
        levelID,
        dataID,
        scoreData.score,
        scoreData.time,
        scoreData.TotalMove,
        scoreData.TotalUndo
    );

    // Tulis langkah-langkah replay (UDRLZ)
    Node *curr = q->front;
    while (curr) {
        ReplayStep *step = (ReplayStep *) curr->data;
        fprintf(fp, "%c", step->move);
        curr = curr->next;
    }

    fprintf(fp, "\n");
    fclose(fp);
}


