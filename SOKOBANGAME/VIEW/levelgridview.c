#define NCURSES_MOUSE_VERSION
#include "levelgridview.h"

// digunakan unutk parsing level pertama agar dapat dihubungkan dengan integer selected
LevelID get_chapter_start_level(chapter_index chapter) {
    switch (chapter) {
        case CHAPTER_1: return LEVEL_1C1;
        case CHAPTER_2: return LEVEL_2C1;
        case CHAPTER_3: return LEVEL_3C1;
        case CHAPTER_4: return LEVEL_4C1;
        case CHAPTER_5: return LEVEL_5C1;
        default: return LEVEL_1C1; // Fallback
    }
}

//dibuat agar lebih modular
void display_leaderboard_or_history(context option, chapter_index chapter, int selected_level_offset, const char username[20]) {
    LevelID start_level = get_chapter_start_level(chapter);
    LevelData current_level = ALL_LEVELS[start_level + selected_level_offset];

    DoublyLinkedList displayList;
    initList(&displayList);
    switch (option)
    {
    case HISTORY:
        load_data_filter_by_name(&displayList, current_level.level_id, username);
        break;
    case LEADERBOARD:
        load_data_filter_by_score(&displayList, current_level.level_id);
        break;
    }

    int ch;
    int prev_lines = LINES;
    int prev_cols = COLS;
    int selected_row = 0;
    int data_count = displayList.size;

    while ((ch = getch()) != 27) { // ESC to exit
        clear();
        handle_resize(&prev_lines, &prev_cols);

        const char* context_str = (option == LEADERBOARD) ? "LEADERBOARD" : "HISTORY";
        char title_text[100];
        snprintf(title_text, sizeof(title_text), "%s - %s", context_str, current_level.level_name);

        Txtbox title = {COLS/2 - strlen(title_text)/2, 2, strlen(title_text) + 4, 2, title_text, "REVERSED"};
        // untuk debugging value parameter
        //mvprintw(0, 0, "Username: %s, LevelID: %s, Records: %d", username, current_level.level_id, displayList.size);
        draw_txtbox(&title);

        int table_width = COLS / 2 + 30;
        int table_height = 14;
        int start_x = (COLS - table_width) / 2;
        int start_y = 6;

        draw_box(start_x, start_y, table_width, table_height);

        int header_y = start_y + 1;
        int rank_x = start_x + 2;
        int user_x = start_x + 12;
        int score_x = start_x + 32;
        int moves_x = start_x + 45;
        int time_x = start_x + 55;
        int undo_x = start_x + 65;
        int replay_x = start_x + 75;

        mvprintw(header_y, rank_x, "RANK");
        mvprintw(header_y, user_x, "USERNAME");
        mvprintw(header_y, score_x, "SCORE");
        mvprintw(header_y, moves_x, "MOVES");
        mvprintw(header_y, time_x, "TIME");
        mvprintw(header_y, undo_x, "UNDO");
        
        draw_horizontal_line(header_y + 1, start_x + 1, table_width - 1);

        if (displayList.size == 0) {
            mvprintw(start_y + 4, start_x + table_width / 2 - 5, "Data Kosong");
        } else {
            TableItems *current = displayList.head;
            for (int i = 0; i < 10 && current != NULL; i++, current = current->next) {
                PlayData *pdata = (PlayData*)current->data;
                int row_y = start_y + 3 + i;
                mvprintw(row_y, rank_x, "%d", i + 1);
                mvprintw(row_y, user_x, "%s", pdata->username);
                mvprintw(row_y, score_x, "%d", pdata->scoreData.score);
                mvprintw(row_y, moves_x, "%d", pdata->scoreData.TotalMove);
                mvprintw(row_y, time_x, "%ds", pdata->scoreData.time);
                mvprintw(row_y, undo_x, "%d", pdata->scoreData.TotalUndo);

                if (i == selected_row) {
                    attron(A_REVERSE);
                }
                mvprintw(row_y, replay_x, "[ REPLAY ]");
                if (i == selected_row) {
                    attroff(A_REVERSE);
                }
            }
        }

        mvprintw(start_y + table_height + 2, start_x, "Gunakan key tanda panah untuk navigasi, ENTER untuk menonton replay, ESC untuk kembali");
        refresh();

        switch (ch) {
            case KEY_UP:
                selected_row = (selected_row > 0) ? selected_row - 1 : (displayList.size > 0 ? displayList.size - 1 : 0);
                break;
            case KEY_DOWN:
                selected_row = (selected_row < displayList.size - 1) ? selected_row + 1 : 0;
                break;
            case '\n':
            case KEY_ENTER:
                if (selected_row >= 0 && selected_row < displayList.size) {
                    //parsing ruangan agar sesuai
                    char dataIDStr[64];
                    RoomLayout room;
                    parse_room(&room, current_level.map);
                    TableItems *current = displayList.head;
                    for (int i = 0; i < selected_row && current != NULL; i++) current = current->next;
                    if (current != NULL) {
                        PlayData *pdata = (PlayData*)current->data;
                        sprintf(dataIDStr, "%d", pdata->ID_data);
                        Queue tempqueue;
                        switch (option)
                        {
                        case HISTORY:
                            loadReplayRecord(&tempqueue, username, dataIDStr);
                            break;
                        case LEADERBOARD:
                            loadReplayRecord(&tempqueue, pdata->username, dataIDStr);
                            break;
                        }
                        playReplay(&room, current_level, &tempqueue);
                        clearReplayQueue(&tempqueue);
                    }
                }
                break;
        }
    }
    // Free the list and PlayData
    TableItems *current = displayList.head;
    while (current != NULL) {
        TableItems *next = current->next;
        free(current->data);
        current = next;
    }
    clearList(&displayList);
}

// Mengembalikan string judul untuk chapter dan konteks tertentu (LEADERBOARD/HISTORY)
const char* get_chapter_title(chapter_index chapter, context option) {
    switch (chapter) {
        case CHAPTER_1:
            switch (option) {
                case LEADERBOARD: return "CHAPTER 1 LEADERBOARD";
                case HISTORY: return "CHAPTER 1 HISTORY";
            }
            break;
        case CHAPTER_2:
            switch (option) {
                case LEADERBOARD: return "CHAPTER 2 LEADERBOARD";
                case HISTORY: return "CHAPTER 2 HISTORY";
            }
            break;
        case CHAPTER_3:
            switch (option) {
                case LEADERBOARD: return "CHAPTER 3 LEADERBOARD";
                case HISTORY: return "CHAPTER 3 HISTORY";
            }
            break;
        case CHAPTER_4:
            switch (option) {
                case LEADERBOARD: return "CHAPTER 4 LEADERBOARD";
                case HISTORY: return "CHAPTER 4 HISTORY";
            }
            break;
        case CHAPTER_5:
            switch (option) {
                case LEADERBOARD: return "CHAPTER 5 LEADERBOARD";
                case HISTORY: return "CHAPTER 5 HISTORY";
            }
            break;
        default:
            return "CHAPTER LEADERBOARD";
    }
    return "CHAPTER LEADERBOARD";
}

// Menampilkan grid level untuk Chapter 1 sesuai konteks (LEADERBOARD/HISTORY)
void ch1_grid(context option, const char username[20]) {
    // Level names for Chapter 1 (adjust if you want to use level_id instead)
    pthread_t soundThread;
    const char* level_names[] = {
        ALL_LEVELS[LEVEL_1C1].level_name,
        ALL_LEVELS[LEVEL_1C2].level_name,
        ALL_LEVELS[LEVEL_1C3].level_name,
        ALL_LEVELS[LEVEL_1C4].level_name,
        ALL_LEVELS[LEVEL_1C5].level_name,
        ALL_LEVELS[LEVEL_1C6].level_name,
        ALL_LEVELS[LEVEL_1C7].level_name,
        ALL_LEVELS[LEVEL_1C8].level_name
    };
    int n_levels = 8;
    int selected = 0;
    int ch;
    int prev_lines = LINES;
    int prev_cols = COLS;

    while ((ch = getch()) != 27) { // ESC to exit
        clear();
        handle_resize(&prev_lines, &prev_cols);
        Txtbox title = {COLS/2 - 10, 2, strlen(get_chapter_title(CHAPTER_1, option)) + 5, 2, (char*)get_chapter_title(CHAPTER_1, option), "REVERSED"};
        draw_txtbox(&title);

        // Layout: vertical list, centered
        int btn_width = COLS / 2;
        int btn_height = 3;
        int start_x = (COLS - btn_width) / 2;
        int start_y = LINES / 2 - (n_levels * (btn_height + 1)) / 2;

        for (int i = 0; i < n_levels; i++) {
            Button btn = {start_x, start_y + i * (btn_height + 1), btn_width, btn_height, (char*)level_names[i]};
            if (i == selected) {
                attron(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            }
            draw_btn(&btn);
            if (i == selected) {
                attroff(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            }
        }

        mvprintw(start_y - 2, start_x, "Gunakan panah atas/bawah untuk navigasi, ESC untuk kembali");
        refresh();

        switch (ch) {
             case KEY_UP:
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                selected = (selected > 0) ? selected - 1 : n_levels - 1;
                break;
            case KEY_DOWN:
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                selected = (selected < n_levels - 1) ? selected + 1 : 0;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&soundThread, NULL, playEnterSound, NULL);
                pthread_detach(soundThread);
                switch(option){
                    case HISTORY:
                        display_leaderboard_or_history(option, CHAPTER_1, selected, username);
                        break;
                    case LEADERBOARD:
                        display_leaderboard_or_history(option, CHAPTER_1, selected, username);
                        break;
                }
                break;
            default:
                break;
        }
    }
}

// Menampilkan grid level untuk Chapter 2 sesuai konteks (LEADERBOARD/HISTORY)
void ch2_grid(context option, const char username[20]) {
    pthread_t soundThread;
    const char* level_names[] = {
        ALL_LEVELS[LEVEL_2C1].level_name,
        ALL_LEVELS[LEVEL_2C2].level_name,
        ALL_LEVELS[LEVEL_2C3].level_name,
        ALL_LEVELS[LEVEL_2C4].level_name,
        ALL_LEVELS[LEVEL_2C5].level_name,
        ALL_LEVELS[LEVEL_2C6].level_name,
        ALL_LEVELS[LEVEL_2C7].level_name,
        ALL_LEVELS[LEVEL_2C8].level_name,
        ALL_LEVELS[LEVEL_2C9].level_name,
        ALL_LEVELS[LEVEL_2C10].level_name,
        ALL_LEVELS[LEVEL_2C11].level_name,
        ALL_LEVELS[LEVEL_2C12].level_name,
        ALL_LEVELS[LEVEL_2C13].level_name,
        ALL_LEVELS[LEVEL_2C14].level_name,
        ALL_LEVELS[LEVEL_2C15].level_name,
        ALL_LEVELS[LEVEL_1B].level_name
    };
    int n_levels = 16;
    int selected = 0;
    int ch;
    int prev_lines = LINES;
    int prev_cols = COLS;

    // Grid config
    btngridprop grid;
    grid.cols = 4;
    grid.btn_width = COLS / (grid.cols + 1);
    grid.btn_height = 3;
    grid.h_spacing = 2;
    grid.v_spacing = 1;
    int rows = (n_levels + grid.cols - 1) / grid.cols;
    int grid_width = grid.cols * grid.btn_width + (grid.cols - 1) * grid.h_spacing;
    int grid_height = rows * grid.btn_height + (rows - 1) * grid.v_spacing;
    grid.start_x = (COLS - grid_width) / 2;
    grid.start_y = LINES / 2 - grid_height / 2;

    while ((ch = getch()) != 27) { // ESC to exit
        clear();
        handle_resize(&prev_lines, &prev_cols);
        Txtbox title = {COLS/2 - 10, 2, strlen(get_chapter_title(CHAPTER_2, option)) + 5, 2, (char*)get_chapter_title(CHAPTER_2, option), "REVERSED"};
        draw_txtbox(&title);

        // Draw grid of buttons using the new module
        draw_button_grid(level_names, n_levels, selected, &grid);

        mvprintw(grid.start_y - 2, grid.start_x, "Gunakan panah untuk navigasi, ESC untuk kembali");
        refresh();

        switch (ch) {
            case KEY_UP: {
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                int row = selected / grid.cols;
                int col = selected % grid.cols;
                if (row > 0) {
                    int above = selected - grid.cols;
                    if (above < n_levels) selected = above;
                }
                break;
            }
            case KEY_DOWN: {
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                int row = selected / grid.cols;
                int col = selected % grid.cols;
                int below = selected + grid.cols;
                if (below < n_levels) {
                    selected = below;
                } else {
                    // If last row is incomplete, stay in same column if possible
                    int last_row_start = (rows - 1) * grid.cols;
                    int last_row_end = n_levels - 1;
                    int new_idx = last_row_start + col;
                    if (new_idx <= last_row_end) selected = new_idx;
                }
                break;
            }
            case KEY_LEFT:
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                if (selected % grid.cols > 0) selected--;
                break;
            case KEY_RIGHT:
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                if ((selected % grid.cols) < (grid.cols - 1) && selected + 1 < n_levels) selected++;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&soundThread, NULL, playEnterSound, NULL);
                pthread_detach(soundThread);
                switch(option){
                    case HISTORY:
                    case LEADERBOARD:
                        display_leaderboard_or_history(option, CHAPTER_2, selected, username);
                        break;
                }
                break;
            default:
                break;
        }
    }
}

// Menampilkan grid level untuk Chapter 3 sesuai konteks (LEADERBOARD/HISTORY)
void ch3_grid(context option, const char username[20]) {
    pthread_t soundThread;
    const char* level_names[] = {
        ALL_LEVELS[LEVEL_3C1].level_name,
        ALL_LEVELS[LEVEL_3C2].level_name,
        ALL_LEVELS[LEVEL_3C3].level_name,
        ALL_LEVELS[LEVEL_3C4].level_name,
        ALL_LEVELS[LEVEL_3C5].level_name,
        ALL_LEVELS[LEVEL_3C6].level_name,
        ALL_LEVELS[LEVEL_3C7].level_name,
        ALL_LEVELS[LEVEL_3C8].level_name,
        ALL_LEVELS[LEVEL_3C9].level_name,
        ALL_LEVELS[LEVEL_3C10].level_name,
        ALL_LEVELS[LEVEL_3C11].level_name,
        ALL_LEVELS[LEVEL_3C12].level_name,
        ALL_LEVELS[LEVEL_3C13].level_name,
        ALL_LEVELS[LEVEL_3C14].level_name,
        ALL_LEVELS[LEVEL_3C15].level_name,
        ALL_LEVELS[LEVEL_3C16].level_name,
        ALL_LEVELS[LEVEL_3C17].level_name,
        ALL_LEVELS[LEVEL_3C18].level_name,
        ALL_LEVELS[LEVEL_2B].level_name
    };
    int n_levels = 19;
    int selected = 0;
    int ch;
    int prev_lines = LINES;
    int prev_cols = COLS;

    // Grid config
    btngridprop grid;
    grid.cols = 5;
    grid.btn_width = COLS / (grid.cols + 1);
    grid.btn_height = 3;
    grid.h_spacing = 2;
    grid.v_spacing = 1;
    int rows = (n_levels + grid.cols - 1) / grid.cols;
    int grid_width = grid.cols * grid.btn_width + (grid.cols - 1) * grid.h_spacing;
    int grid_height = rows * grid.btn_height + (rows - 1) * grid.v_spacing;
    grid.start_x = (COLS - grid_width) / 2;
    grid.start_y = LINES / 2 - grid_height / 2;

    while ((ch = getch()) != 27) { // ESC to exit
        clear();
        handle_resize(&prev_lines, &prev_cols);
        Txtbox title = {COLS/2 - 10, 2, strlen(get_chapter_title(CHAPTER_3, option)) + 5, 2, (char*)get_chapter_title(CHAPTER_3, option), "REVERSED"};
        draw_txtbox(&title);

        draw_button_grid(level_names, n_levels, selected, &grid);

        mvprintw(grid.start_y - 2, grid.start_x, "Gunakan panah untuk navigasi, ESC untuk kembali");
        refresh();

        switch (ch) {
            case KEY_UP: {
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                int row = selected / grid.cols;
                int col = selected % grid.cols;
                if (row > 0) {
                    int above = selected - grid.cols;
                    if (above < n_levels) selected = above;
                }
                break;
            }
            case KEY_DOWN: {
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                int row = selected / grid.cols;
                int col = selected % grid.cols;
                int below = selected + grid.cols;
                if (below < n_levels) {
                    selected = below;
                } else {
                    int last_row_start = (rows - 1) * grid.cols;
                    int last_row_end = n_levels - 1;
                    int new_idx = last_row_start + col;
                    if (new_idx <= last_row_end) selected = new_idx;
                }
                break;
            }
            case KEY_LEFT:
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                if (selected % grid.cols > 0) selected--;
                break;
            case KEY_RIGHT:
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                if ((selected % grid.cols) < (grid.cols - 1) && selected + 1 < n_levels) selected++;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&soundThread, NULL, playEnterSound, NULL);
                pthread_detach(soundThread);
                switch(option){
                    case HISTORY:
                    case LEADERBOARD:
                        display_leaderboard_or_history(option, CHAPTER_3, selected, username);
                        break;
                }
                break;
            default:
                break;
        }
    }
}

// Menampilkan grid level untuk Chapter 4 sesuai konteks (LEADERBOARD/HISTORY)
void ch4_grid(context option, const char username[20]) {
    pthread_t soundThread;
    const char* level_names[] = {
        ALL_LEVELS[LEVEL_4C1].level_name,
        ALL_LEVELS[LEVEL_4C2].level_name,
        ALL_LEVELS[LEVEL_4C3].level_name,
        ALL_LEVELS[LEVEL_4C4].level_name,
        ALL_LEVELS[LEVEL_4C5].level_name,
        ALL_LEVELS[LEVEL_4C6].level_name,
        ALL_LEVELS[LEVEL_4C7].level_name,
        ALL_LEVELS[LEVEL_4C8].level_name,
        ALL_LEVELS[LEVEL_4C9].level_name,
        ALL_LEVELS[LEVEL_4C10].level_name,
        ALL_LEVELS[LEVEL_4C11].level_name,
        ALL_LEVELS[LEVEL_4C12].level_name,
        ALL_LEVELS[LEVEL_4C13].level_name,
        ALL_LEVELS[LEVEL_4C14].level_name,
        ALL_LEVELS[LEVEL_4C15].level_name,
        ALL_LEVELS[LEVEL_4C16].level_name,
        ALL_LEVELS[LEVEL_4C17].level_name,
        ALL_LEVELS[LEVEL_4C18].level_name,
        ALL_LEVELS[LEVEL_4C19].level_name,
        ALL_LEVELS[LEVEL_4C20].level_name,
        ALL_LEVELS[LEVEL_4C21].level_name,
        ALL_LEVELS[LEVEL_3B].level_name
    };
    int n_levels = 22;
    int selected = 0;
    int ch;
    int prev_lines = LINES;
    int prev_cols = COLS;

    // Grid config
    btngridprop grid;
    grid.cols = 5;
    grid.btn_width = COLS / (grid.cols + 1);
    grid.btn_height = 3;
    grid.h_spacing = 2;
    grid.v_spacing = 1;
    int rows = (n_levels + grid.cols - 1) / grid.cols;
    int grid_width = grid.cols * grid.btn_width + (grid.cols - 1) * grid.h_spacing;
    int grid_height = rows * grid.btn_height + (rows - 1) * grid.v_spacing;
    grid.start_x = (COLS - grid_width) / 2;
    grid.start_y = LINES / 2 - grid_height / 2;

    while ((ch = getch()) != 27) { // ESC to exit
        clear();
        handle_resize(&prev_lines, &prev_cols);
        Txtbox title = {COLS/2 - 10, 2, strlen(get_chapter_title(CHAPTER_4, option)) + 5, 2, (char*)get_chapter_title(CHAPTER_4, option), "REVERSED"};
        draw_txtbox(&title);

        draw_button_grid(level_names, n_levels, selected, &grid);

        mvprintw(grid.start_y - 2, grid.start_x, "Gunakan panah untuk navigasi, ESC untuk kembali");
        refresh();

        switch (ch) {
            case KEY_UP: {
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                int row = selected / grid.cols;
                int col = selected % grid.cols;
                if (row > 0) {
                    int above = selected - grid.cols;
                    if (above < n_levels) selected = above;
                }
                break;
            }
            case KEY_DOWN: {
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                int row = selected / grid.cols;
                int col = selected % grid.cols;
                int below = selected + grid.cols;
                if (below < n_levels) {
                    selected = below;
                } else {
                    int last_row_start = (rows - 1) * grid.cols;
                    int last_row_end = n_levels - 1;
                    int new_idx = last_row_start + col;
                    if (new_idx <= last_row_end) selected = new_idx;
                }
                break;
            }
            case KEY_LEFT:
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                if (selected % grid.cols > 0) selected--;
                break;
            case KEY_RIGHT:
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                if ((selected % grid.cols) < (grid.cols - 1) && selected + 1 < n_levels) selected++;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&soundThread, NULL, playEnterSound, NULL);
                pthread_detach(soundThread);
                switch(option){
                    case HISTORY:
                    case LEADERBOARD:
                        display_leaderboard_or_history(option, CHAPTER_4, selected, username);
                        break;
                }
                break;
            default:
                break;
        }
    }
}

// Menampilkan grid level untuk Chapter 5 sesuai konteks (LEADERBOARD/HISTORY)
void ch5_grid(context option, const char username[20]) {
    pthread_t soundThread;
    const char* level_names[] = {
        ALL_LEVELS[LEVEL_5C1].level_name,
        ALL_LEVELS[LEVEL_5C2].level_name,
        ALL_LEVELS[LEVEL_5C3].level_name,
        ALL_LEVELS[LEVEL_5C4].level_name,
        ALL_LEVELS[LEVEL_5C5].level_name,
        ALL_LEVELS[LEVEL_5C6].level_name,
        ALL_LEVELS[LEVEL_5C7].level_name,
        ALL_LEVELS[LEVEL_5C8].level_name,
        ALL_LEVELS[LEVEL_5C9].level_name,
        ALL_LEVELS[LEVEL_5C10].level_name,
        ALL_LEVELS[LEVEL_5C11].level_name,
        ALL_LEVELS[LEVEL_5C12].level_name,
        ALL_LEVELS[LEVEL_5C13].level_name,
        ALL_LEVELS[LEVEL_5C14].level_name,
        ALL_LEVELS[LEVEL_5C15].level_name,
        ALL_LEVELS[LEVEL_5C16].level_name,
        ALL_LEVELS[LEVEL_5C17].level_name,
        ALL_LEVELS[LEVEL_5C18].level_name,
        ALL_LEVELS[LEVEL_5C19].level_name,
        ALL_LEVELS[LEVEL_5C20].level_name,
        ALL_LEVELS[LEVEL_5C21].level_name,
        ALL_LEVELS[LEVEL_5C22].level_name,
        ALL_LEVELS[LEVEL_5B].level_name,
        ALL_LEVELS[LEVEL_6B].level_name
    };
    int n_levels = 24;
    int selected = 0;
    int ch;
    int prev_lines = LINES;
    int prev_cols = COLS;

    // Grid config
    btngridprop grid;
    grid.cols = 6;
    grid.btn_width = COLS / (grid.cols + 1);
    grid.btn_height = 3;
    grid.h_spacing = 2;
    grid.v_spacing = 1;
    int rows = (n_levels + grid.cols - 1) / grid.cols;
    int grid_width = grid.cols * grid.btn_width + (grid.cols - 1) * grid.h_spacing;
    int grid_height = rows * grid.btn_height + (rows - 1) * grid.v_spacing;
    grid.start_x = (COLS - grid_width) / 2;
    grid.start_y = LINES / 2 - grid_height / 2;

    while ((ch = getch()) != 27) { // ESC to exit
        clear();
        handle_resize(&prev_lines, &prev_cols);
        Txtbox title = {COLS/2 - 10, 2, strlen(get_chapter_title(CHAPTER_5, option)) + 5, 2, (char*)get_chapter_title(CHAPTER_5, option), "REVERSED"};
        draw_txtbox(&title);

        draw_button_grid(level_names, n_levels, selected, &grid);

        mvprintw(grid.start_y - 2, grid.start_x, "Gunakan panah untuk navigasi, ESC untuk kembali");
        refresh();

        switch (ch) {
            case KEY_UP: {
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                int row = selected / grid.cols;
                int col = selected % grid.cols;
                if (row > 0) {
                    int above = selected - grid.cols;
                    if (above < n_levels) selected = above;
                }
                break;
            }
            case KEY_DOWN: {
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                int row = selected / grid.cols;
                int col = selected % grid.cols;
                int below = selected + grid.cols;
                if (below < n_levels) {
                    selected = below;
                } else {
                    int last_row_start = (rows - 1) * grid.cols;
                    int last_row_end = n_levels - 1;
                    int new_idx = last_row_start + col;
                    if (new_idx <= last_row_end) selected = new_idx;
                }
                break;
            }
            case KEY_LEFT:
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                if (selected % grid.cols > 0) selected--;
                break;
            case KEY_RIGHT:
                pthread_create(&soundThread, NULL, playArrowSound, NULL);
                pthread_detach(soundThread);
                if ((selected % grid.cols) < (grid.cols - 1) && selected + 1 < n_levels) selected++;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&soundThread, NULL, playEnterSound, NULL);
                pthread_detach(soundThread);
                switch(option){
                    case HISTORY:
                    case LEADERBOARD:
                        display_leaderboard_or_history(option, CHAPTER_5, selected, username);
                        break;
                }
                break;
            default:
                break;
        }
    }
}


