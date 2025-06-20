#define NCURSES_MOUSE_VERSION
#include "levelgridview.h"
#include "../GAMEPLAY/DB_ACCESS/SaveState.h"
#include "../GAMEPLAY/GAME_LOGIC/ScoreGame.h"
#include "../GAMEPLAY/REPLAY_LOGIC/ReplayGame.h"
#include "../GAMEPLAY/ARENA_LOGIC/RoomFactory.h"

void ch1_leaderboard_table(int selected){
    PlayData dummy_data[10] = {
        {"Player1", "LEVEL_1C1", 1, {1000, 120, 50, 5}},
        {"Player2", "LEVEL_1C1", 2, {950, 130, 55, 6}},
        {"Player3", "LEVEL_1C1", 3, {900, 140, 60, 7}},
        {"Player4", "LEVEL_1C1", 4, {850, 150, 65, 8}},
        {"Player5", "LEVEL_1C1", 5, {800, 160, 70, 9}},
        {"Player6", "LEVEL_1C1", 6, {750, 170, 75, 10}},
        {"Player7", "LEVEL_1C1", 7, {700, 180, 80, 11}},
        {"Player8", "LEVEL_1C1", 8, {650, 190, 85, 12}},
        {"Player9", "LEVEL_1C1", 9, {600, 200, 90, 13}},
        {"Player10", "LEVEL_1C1", 10, {550, 210, 95, 14}}
    };

    int ch;
    int prev_lines = LINES;
    int prev_cols = COLS;
    int selected_row = 0;

    while ((ch = getch()) != 27) { // ESC to exit
        clear();
        handle_resize(&prev_lines, &prev_cols);

        // Get level name based on selected index
        const char* level_name = ALL_LEVELS[LEVEL_1C1 + selected].level_name;
        char title_text[100];
        snprintf(title_text, sizeof(title_text), "LEADERBOARD - %s", level_name);

        Txtbox title = {COLS/2 - strlen(title_text)/2, 2, strlen(title_text) + 4, 2, title_text, "REVERSED"};
        draw_txtbox(&title);

        int table_width = COLS / 2 + 30;
        int table_height = 14;
        int start_x = (COLS - table_width) / 2;
        int start_y = 6;

        // Draw table border
        draw_box(start_x, start_y, table_width, table_height);

        // Draw headers
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
        
        // Draw horizontal line under header
        draw_horizontal_line(header_y + 1, start_x + 1, table_width - 1);


        // Draw data
        for (int i = 0; i < 10; i++) {
            int row_y = start_y + 3 + i;
            mvprintw(row_y, rank_x, "%d", i + 1);
            mvprintw(row_y, user_x, "%s", dummy_data[i].username);
            mvprintw(row_y, score_x, "%d", dummy_data[i].scoreData.score);
            mvprintw(row_y, moves_x, "%d", dummy_data[i].scoreData.TotalMove);
            mvprintw(row_y, time_x, "%ds", dummy_data[i].scoreData.time);
            mvprintw(row_y, undo_x, "%d", dummy_data[i].scoreData.TotalUndo);

            // Draw replay button
            if (i == selected_row) {
                attron(A_REVERSE);
            }
            mvprintw(row_y, replay_x, "[ REPLAY ]");
            if (i == selected_row) {
                attroff(A_REVERSE);
            }
        }

        mvprintw(start_y + table_height + 2, start_x, "Gunakan key tanda panah untuk navigasi, ENTER untuk menonton replay, ESC untuk kembali");
        refresh();

        switch (ch) {
            case KEY_UP:
                selected_row = (selected_row > 0) ? selected_row - 1 : 9;
                break;
            case KEY_DOWN:
                selected_row = (selected_row < 9) ? selected_row + 1 : 0;
                break;
            case '\n':
            case KEY_ENTER:
                if (selected_row >= 0 && selected_row < 10) {
                    //parsing ruangan agar ruangan sesuai
                    LevelData current_level = ALL_LEVELS[LEVEL_1C1 + selected];
                    RoomLayout room;
                    parse_room(&room, current_level.map);

                    Queue replay_queue;
                    initQueue(&replay_queue);
                    //Replay dummy
                    enqueue(&replay_queue, createStep('R'));
                    enqueue(&replay_queue, createStep('R'));
                    enqueue(&replay_queue, createStep('D'));
                    enqueue(&replay_queue, createStep('D'));
                    enqueue(&replay_queue, createStep('L'));
                    enqueue(&replay_queue, createStep('L'));
                    enqueue(&replay_queue, createStep('U'));
                    enqueue(&replay_queue, createStep('U'));
                    enqueue(&replay_queue, createStep('Z'));

                    playReplay(&room, current_level, &replay_queue);
                    clearReplayQueue(&replay_queue);
                }
                break;
        }
    }
}

void ch1_history_table(int selected){
        PlayData dummy_data[10] = {
        {"Player1", "LEVEL_1C1", 1, {1000, 120, 50, 5}},
        {"Player2", "LEVEL_1C1", 2, {950, 130, 55, 6}},
        {"Player3", "LEVEL_1C1", 3, {900, 140, 60, 7}},
        {"Player4", "LEVEL_1C1", 4, {850, 150, 65, 8}},
        {"Player5", "LEVEL_1C1", 5, {800, 160, 70, 9}},
        {"Player6", "LEVEL_1C1", 6, {750, 170, 75, 10}},
        {"Player7", "LEVEL_1C1", 7, {700, 180, 80, 11}},
        {"Player8", "LEVEL_1C1", 8, {650, 190, 85, 12}},
        {"Player9", "LEVEL_1C1", 9, {600, 200, 90, 13}},
        {"Player10", "LEVEL_1C1", 10, {550, 210, 95, 14}}
    };

    int ch;
    int prev_lines = LINES;
    int prev_cols = COLS;
    int selected_row = 0;

    while ((ch = getch()) != 27) { // ESC to exit
        clear();
        handle_resize(&prev_lines, &prev_cols);

        // Get level name based on selected index
        const char* level_name = ALL_LEVELS[LEVEL_1C1 + selected].level_name;
        char title_text[100];
        snprintf(title_text, sizeof(title_text), "HISTORY - %s", level_name);

        Txtbox title = {COLS/2 - strlen(title_text)/2, 2, strlen(title_text) + 4, 2, title_text, "REVERSED"};
        draw_txtbox(&title);

        int table_width = COLS / 2 + 30;
        int table_height = 14;
        int start_x = (COLS - table_width) / 2;
        int start_y = 6;

        // Draw table border
        draw_box(start_x, start_y, table_width, table_height);

        // Draw headers
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
        
        // Draw horizontal line under header
        draw_horizontal_line(header_y + 1, start_x + 1, table_width - 1);


        // Draw data
        for (int i = 0; i < 10; i++) {
            int row_y = start_y + 3 + i;
            mvprintw(row_y, rank_x, "%d", i + 1);
            mvprintw(row_y, user_x, "%s", dummy_data[i].username);
            mvprintw(row_y, score_x, "%d", dummy_data[i].scoreData.score);
            mvprintw(row_y, moves_x, "%d", dummy_data[i].scoreData.TotalMove);
            mvprintw(row_y, time_x, "%ds", dummy_data[i].scoreData.time);
            mvprintw(row_y, undo_x, "%d", dummy_data[i].scoreData.TotalUndo);

            // Draw replay button
            if (i == selected_row) {
                attron(A_REVERSE);
            }
            mvprintw(row_y, replay_x, "[ REPLAY ]");
            if (i == selected_row) {
                attroff(A_REVERSE);
            }
        }

        mvprintw(start_y + table_height + 2, start_x, "Gunakan key tanda panah untuk navigasi, ENTER untuk menonton replay, ESC untuk kembali");
        refresh();

        switch (ch) {
            case KEY_UP:
                selected_row = (selected_row > 0) ? selected_row - 1 : 9;
                break;
            case KEY_DOWN:
                selected_row = (selected_row < 9) ? selected_row + 1 : 0;
                break;
            case '\n':
            case KEY_ENTER:
                if (selected_row >= 0 && selected_row < 10) {
                    //parsing ruangan agar ruangan sesuai
                    LevelData current_level = ALL_LEVELS[LEVEL_1C1 + selected];
                    RoomLayout room;
                    parse_room(&room, current_level.map);

                    Queue replay_queue;
                    initQueue(&replay_queue);
                    //Replay dummy
                    enqueue(&replay_queue, createStep('R'));
                    enqueue(&replay_queue, createStep('R'));
                    enqueue(&replay_queue, createStep('D'));
                    enqueue(&replay_queue, createStep('D'));
                    enqueue(&replay_queue, createStep('L'));
                    enqueue(&replay_queue, createStep('L'));
                    enqueue(&replay_queue, createStep('U'));
                    enqueue(&replay_queue, createStep('U'));
                    enqueue(&replay_queue, createStep('Z'));

                    playReplay(&room, current_level, &replay_queue);
                    clearReplayQueue(&replay_queue);
                }
                break;
        }
    }
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
void ch1_grid(context option) {
    // Level names for Chapter 1 (adjust if you want to use level_id instead)
    pthread_t enterSound, arrowSound;    
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
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                selected = (selected > 0) ? selected - 1 : n_levels - 1;
                break;
            case KEY_DOWN:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                selected = (selected < n_levels - 1) ? selected + 1 : 0;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                switch(option){
                    case HISTORY:
                        ch1_history_table(selected);
                        break;
                    case LEADERBOARD:
                        ch1_leaderboard_table(selected);
                        break;
                }
                break;
            default:
                break;
        }
    }
}

// Menampilkan grid level untuk Chapter 2 sesuai konteks (LEADERBOARD/HISTORY)
void ch2_grid(context option) {
    pthread_t enterSound, arrowSound;
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
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                int row = selected / grid.cols;
                int col = selected % grid.cols;
                if (row > 0) {
                    int above = selected - grid.cols;
                    if (above < n_levels) selected = above;
                }
                break;
            }
            case KEY_DOWN: {
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
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
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if (selected % grid.cols > 0) selected--;
                break;
            case KEY_RIGHT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if ((selected % grid.cols) < (grid.cols - 1) && selected + 1 < n_levels) selected++;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                switch(option){
                    case HISTORY:
                    case LEADERBOARD:
                }
                break;
            default:
                break;
        }
    }
}

// Menampilkan grid level untuk Chapter 3 sesuai konteks (LEADERBOARD/HISTORY)
void ch3_grid(context option) {
    pthread_t enterSound, arrowSound;
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
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                int row = selected / grid.cols;
                int col = selected % grid.cols;
                if (row > 0) {
                    int above = selected - grid.cols;
                    if (above < n_levels) selected = above;
                }
                break;
            }
            case KEY_DOWN: {
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
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
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if (selected % grid.cols > 0) selected--;
                break;
            case KEY_RIGHT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if ((selected % grid.cols) < (grid.cols - 1) && selected + 1 < n_levels) selected++;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                switch(option){
                    case HISTORY:
                    case LEADERBOARD:
                }
                break;
            default:
                break;
        }
    }
}

// Menampilkan grid level untuk Chapter 4 sesuai konteks (LEADERBOARD/HISTORY)
void ch4_grid(context option) {
    pthread_t enterSound, arrowSound;
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
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                int row = selected / grid.cols;
                int col = selected % grid.cols;
                if (row > 0) {
                    int above = selected - grid.cols;
                    if (above < n_levels) selected = above;
                }
                break;
            }
            case KEY_DOWN: {
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
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
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if (selected % grid.cols > 0) selected--;
                break;
            case KEY_RIGHT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if ((selected % grid.cols) < (grid.cols - 1) && selected + 1 < n_levels) selected++;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                switch(option){
                    case HISTORY:
                    case LEADERBOARD:
                }
                break;
            default:
                break;
        }
    }
}

// Menampilkan grid level untuk Chapter 5 sesuai konteks (LEADERBOARD/HISTORY)
void ch5_grid(context option) {
    pthread_t enterSound, arrowSound;
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
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                int row = selected / grid.cols;
                int col = selected % grid.cols;
                if (row > 0) {
                    int above = selected - grid.cols;
                    if (above < n_levels) selected = above;
                }
                break;
            }
            case KEY_DOWN: {
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
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
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if (selected % grid.cols > 0) selected--;
                break;
            case KEY_RIGHT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if ((selected % grid.cols) < (grid.cols - 1) && selected + 1 < n_levels) selected++;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                switch(option){
                    case HISTORY:
                    case LEADERBOARD:
                }
                break;
            default:
                break;
        }
    }
}