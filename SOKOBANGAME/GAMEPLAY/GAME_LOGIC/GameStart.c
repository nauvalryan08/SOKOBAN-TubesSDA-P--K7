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

    stack_init(&StackUndo);
    initQueue(&replayQueue);

    //-----------------------------//

    // --> Parsing data untuk RoomLayout <-- //

    // Cek apakah ada save untuk level ini
    RoomLayout tempRoom;
    if (load_game_state(username, level->level_id, &tempRoom)) {
        if (ask_continue_save()) {
            *room = tempRoom;

            //hapus data yang dipakai
            remove_game_state_entry(username, level->level_id);
        } else {
            parse_room(room, level->map);
            remove_game_state_entry(username, level->level_id);
        }
    } else {
        parse_room(room, level->map);
    }
    //-----------------------------//

    nodelay(stdscr, TRUE);
    //simpan data roomLayout ke undo stack
    save_state(&StackUndo, room);


    // --> Game Loop
    getch();
    while (1) {
        prev_lines = LINES;
        prev_cols = COLS;

        handle_resize(&prev_lines, &prev_cols);

        scoreData.time = global_timer;

        update_box_activation_status (room);
        update_finish_activation_status (room);

        handle_input (room, map, &StackUndo, &replayQueue, &keyOutput, &btn, username);


        if (keyOutput == 27) {
            nodelay(stdscr, FALSE);
            tempOutput = exit_game(room, username, level->level_id);
            if (tempOutput == 0) {
                continue;
            } else if (tempOutput == 1) {
                break;
            }
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
    pthread_t enterSound;

    pthread_create(&winSound, NULL, playWinSound, NULL);
    pthread_join(winSound, NULL);

    char *msg1 = "^_^ CONGRATULATION. YOU WIN! ^_^";
    char *msg2 = "1. Replay  | 2. Next Stage  | 3. Quit";
    Txtbox text[] = {{COLS / 2 - strlen(msg1)/2 - 2, LINES / 2 - 4, strlen(msg1) + 4, 2, msg1, "BOLD"},{COLS / 2 - strlen(msg1)/2 - 4, LINES / 2 - 1, strlen(msg2) + 4, 2, msg2, "BOLD"}};

    // Unlock level berikutnya
    level->is_finished = true;
    Ptree node = findTreeNode(current_chapter->ChapterTree, (void*)level, compareDataID);
    if (node != NULL) {
        unlock_child_if_parent_finished(node);
    }

    // Simpan replay ke database
    char dataID[64];
    sprintf(dataID, "%s_%ld", level->level_id, time(NULL)); // Format unik ID
    save_data_to_database(replayQueue, username, level->level_id, dataID, scoreData);

    // Pilihan pasca menang
    int ch;
    while (1) {
        handle_resize(&prev_lines, &prev_cols);

        draw_txtbox(&text[0]);
        draw_txtbox(&text[1]);

        refresh();

        ch = getch();
        if (ch == '1') {
            // Replay langkah yang baru saja dimainkan
            initReplayQueue(&q);
            if (loadReplayRecord(&q, username, dataID)) {
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                pthread_join(enterSound, NULL);
                playReplay(room, *level, &q);
            } else {
                mvprintw(LINES / 2 + 3, COLS/2 - 9, "Replay tidak ditemukan!");
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


//===> Exiting Game (save state or no)

int exit_game(RoomLayout *room, const char *username, const char *level_id) {
    if (!validate_ExitGame()) {
        return 0; // Lanjutkan game
    }

    // Jika user memilih y untuk exit, tanyakan apakah ingin save
    if (validate_SaveGame()) {
        save_game_state(username, level_id, room);
        showMsg_SaveSuccess();
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

    int ch = getch();
    ch = tolower(ch);

    return ch == 'y';
}




//=================================================//
//==                DATABASE ACCESS              ==//
//=================================================//
/* {Sopian} */

//==> Memnyimpan Hasil data usai bermain
void save_data_to_database ( Queue *q, const char *username, const char *levelID, const char *dataID, ScoreData scoreData) {

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


//==> menyimpan State permainan saat Exit [untuk kembali dilanjutkan saat bermain lagi]
void save_game_state (const char* username, const char* level_id, RoomLayout* room) {
    SaveState save;
    strncpy(save.username, username, sizeof(save.username));
    strncpy(save.level_id, level_id, sizeof(save.level_id));
    save.room = *room;

    // Buka file index lama untuk baca
    FILE *index_old = fopen(INDEX_DATA_STATE_PATH, "r");
    FILE *index_new = fopen("temp_index.txt", "w"); // file index baru
    if (!index_new) return;

    char key_to_remove[64];
    sprintf(key_to_remove, "%s-%s", username, level_id);

    // Salin semua index kecuali yang ingin dihapus
    if (index_old) {
        char line[100], fileKey[64];
        long offset;
        while (fgets(line, sizeof(line), index_old)) {
            sscanf(line, "%[^;];%ld", fileKey, &offset);
            if (strcmp(fileKey, key_to_remove) != 0) {
                fputs(line, index_new);
            }
        }
        fclose(index_old);
    }

    // Buka data file dan tulis data baru
    FILE *data = fopen(DATA_STATE_PATH, "ab");
    if (!data) {
        fclose(index_new);
        return;
    }

    long offset = ftell(data);
    fwrite(&save, sizeof(SaveState), 1, data);
    fclose(data);

    // Tambahkan entri index baru
    fprintf(index_new, "%s;%ld\n", key_to_remove, offset);
    fclose(index_new);

    // Ganti file index lama dengan yang baru
    remove(INDEX_DATA_STATE_PATH);
    rename("temp_index.txt", INDEX_DATA_STATE_PATH);
}


//==> Load gameState (mengambil data RoomLayout untuk nanti dijadikan aacuan start game)
int load_game_state (const char* username, const char* level_id, RoomLayout* room) {
    FILE *index = fopen(INDEX_DATA_STATE_PATH, "r");    //read 
    FILE *data = fopen(DATA_STATE_PATH, "rb");     //read Binary
    if (!index || !data) return 0; //Gagal membuka file

    char line[100], key[40];
    sprintf(key, "%s-%s", username, level_id);
    long offset = -1;       //

    char fileKey[40];
    long fileOffset;

    while (fgets(line, sizeof(line), index)) {
        sscanf(line, "%[^;];%ld", fileKey, &fileOffset);    //mengambil data dengamn format
        if (strcmp(fileKey, key) == 0) {                // JIka sama key nya
            offset = fileOffset;
            break;
        }
    }

    fclose(index);  //index didapatkan
    if (offset == -1) { //data tidak dotermukan sama sekali
        fclose(data);
        return 0;       //tidak ditemukan
    }

    fseek(data, offset, SEEK_SET);
    SaveState loaded;
    fread(&loaded, sizeof(SaveState), 1, data);
    *room = loaded.room;
    fclose(data);
    return 1;

}

// ===> menghapus data state yang sudah dipakai

void remove_game_state_entry(const char* username, const char* level_id) {
    FILE *index_old = fopen(INDEX_DATA_STATE_PATH, "r");
    FILE *data_old = fopen(DATA_STATE_PATH, "rb");
    FILE *index_new = fopen("temp_index.txt", "w");
    FILE *data_new = fopen("temp_data.dat", "wb");

    if (!index_old || !data_old || !index_new || !data_new) {
        if (index_old) fclose(index_old);
        if (data_old) fclose(data_old);
        if (index_new) fclose(index_new);
        if (data_new) fclose(data_new);
        return;
    }

    char key_to_remove[64];
    sprintf(key_to_remove, "%s-%s", username, level_id);

    char line[100], fileKey[64];
    long fileOffset;
    SaveState buffer;
    long new_offset = 0;

    while (fgets(line, sizeof(line), index_old)) {
        sscanf(line, "%[^;];%ld", fileKey, &fileOffset);

        // Pindah ke offset di data lama
        fseek(data_old, fileOffset, SEEK_SET);
        fread(&buffer, sizeof(SaveState), 1, data_old);

        // Jika bukan data yang ingin dihapus, tulis ulang ke file baru
        if (strcmp(fileKey, key_to_remove) != 0) {
            // tulis ke data baru
            fwrite(&buffer, sizeof(SaveState), 1, data_new);
            // tulis ke index baru dengan offset baru
            fprintf(index_new, "%s;%ld\n", fileKey, new_offset);
            new_offset += sizeof(SaveState);
        }
    }

    // Tutup semua
    fclose(index_old);
    fclose(data_old);
    fclose(index_new);
    fclose(data_new);

    // Replace file lama dengan yang baru
    remove(INDEX_DATA_STATE_PATH);
    remove(DATA_STATE_PATH);
    rename("temp_index.txt", INDEX_DATA_STATE_PATH);
    rename("temp_data.dat", DATA_STATE_PATH);
}
