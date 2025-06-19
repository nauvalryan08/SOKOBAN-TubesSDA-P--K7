#define NCURSES_MOUSE_VERSION
#include "leaderboard.h"

void show_leaderboard(){
    mmask_t old;
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, &old);
    keypad(stdscr, TRUE);
    MEVENT event;

    int selected = 0;
    int ch;
    int prev_lines =  LINES;
    int prev_cols = COLS;

    while ((ch = getch()) != 27){
        clear();
        handle_resize(&prev_lines, &prev_cols);
        Txtbox title = {COLS/2 - 10, 2, strlen("LEADERBOARD") + 5, 2, "LEADERBOARD", "REVERSED"};
        Button buttons[] = {
            {COLS / 4, LINES / 2 - 15, COLS / 2, 4, "Chapter 1"},
            {COLS / 4, LINES / 2 - 10, COLS / 2, 4, "Chapter 2"},
            {COLS / 4, LINES / 2 - 5, COLS / 2, 4, "Chapter 3"},
            {COLS / 4, LINES / 2, COLS / 2, 4, "Chapter 4"},
            {COLS / 4, LINES / 2 + 5, COLS / 2, 4, "Chapter 5"},
        };

        pthread_t enterSound, arrowSound;
        switch (ch){
            case KEY_UP:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                selected = (selected > 0) ? selected - 1 : n_chapters - 1;
                break;
            case KEY_DOWN:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                selected = (selected < n_chapters - 1) ? selected + 1 : 0;
                break;
            case '\n':
            case KEY_ENTER:
                switch (selected){
                    case 0: // Chapter 1
                    pthread_create(&enterSound, NULL, playEnterSound, NULL);
                    ch1_leaderboard();
                    break;
                    case 1: // Chapter 2
                    pthread_create(&enterSound, NULL, playEnterSound, NULL);
                    ch2_leaderboard();
                    break;
                    case 2: // Chapter 3
                    pthread_create(&enterSound, NULL, playEnterSound, NULL);
                    ch3_leaderboard();
                    break;
                    case 3: // Chapter 4
                    pthread_create(&enterSound, NULL, playEnterSound, NULL);
                    ch4_leaderboard();
                    break;
                    case 4: // Chapter 5
                    pthread_create(&enterSound, NULL, playEnterSound, NULL);
                    ch5_leaderboard();
                    break;
                }
            case KEY_MOUSE:
                if (getmouse(&event) == OK) {
                    if (event.bstate & BUTTON1_CLICKED){
                        pthread_create(&enterSound, NULL, playEnterSound, NULL);
                        for (int i = 0; i < n_chapters; i++) {
                            if (isbtnarea(&buttons[i], event.x, event.y)) {
                                selected = i;
                            }
                        }
                    }
                    else if (event.bstate & BUTTON1_DOUBLE_CLICKED){
                        for (int i = 0; i < n_chapters; i++) {
                            if (isbtnarea(&buttons[i], event.x, event.y)) {
                                selected = i;
                                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                                    switch (selected){
                                        case 0: // Chapter 1
                                        pthread_create(&enterSound, NULL, playEnterSound, NULL);
                                        ch1_leaderboard();
                                        break;
                                        case 1: // Chapter 2
                                        pthread_create(&enterSound, NULL, playEnterSound, NULL);
                                        ch2_leaderboard();
                                        break;
                                        case 2: // Chapter 3
                                        pthread_create(&enterSound, NULL, playEnterSound, NULL);
                                        ch3_leaderboard();
                                        break;
                                        case 3: // Chapter 4
                                        pthread_create(&enterSound, NULL, playEnterSound, NULL);
                                        ch4_leaderboard();
                                        break;
                                        case 4: // Chapter 5
                                        pthread_create(&enterSound, NULL, playEnterSound, NULL);
                                        ch5_leaderboard();
                                        break;
                                    }
                            }
                        }
                    }
                }
                break;
            case KEY_RESIZE:
                resize_term(0,0);
                break;
            default:
                break;
        }
        pthread_join(arrowSound, NULL);
        pthread_join(enterSound, NULL);

        // Instruksi
        draw_box(0,0,strlen("Klik kiri pada tombol chapter untuk memilih chapter!") + 2, 5);
        mvprintw(1, 1, "Klik kiri pada tombol chapter untuk memilih chapter!");
        mvprintw(2, 1, "Atau gunakan tombol panah atas/bawah untuk navigasi");
        mvprintw(3, 1, "Gunakan tombol ESC untuk kembali ke menu utama");
        mvprintw(4, 1, "Tekan ENTER untuk memilih chapter");
        draw_txtbox(&title);

        // menampilkan button
        for (int i = 0; i < n_chapters; i++) {
            if (i == selected) {
                attron(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            }
            draw_btn(&buttons[i]);
            if (i == selected) {
                attroff(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            }
        }
        refresh();
    }
}

void ch1_leaderboard() {
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
        Txtbox title = {COLS/2 - 10, 2, strlen("CHAPTER 1 LEADERBOARD") + 5, 2, "CHAPTER 1 LEADERBOARD", "REVERSED"};
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
                break;
            default:
                break;
        }
    }
}

void ch2_leaderboard() {
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
    int cols = 4; // 4 columns for 15 levels (last row will have 3)
    int rows = (n_levels + cols - 1) / cols;
    int btn_width = COLS / (cols + 1); // leave some margin
    int btn_height = 3;
    int h_spacing = 2;
    int v_spacing = 1;
    int grid_width = cols * btn_width + (cols - 1) * h_spacing;
    int grid_height = rows * btn_height + (rows - 1) * v_spacing;
    int start_x = (COLS - grid_width) / 2;
    int start_y = LINES / 2 - grid_height / 2;

    while ((ch = getch()) != 27) { // ESC to exit
        clear();
        handle_resize(&prev_lines, &prev_cols);
        Txtbox title = {COLS/2 - 10, 2, strlen("CHAPTER 2 LEADERBOARD") + 5, 2, "CHAPTER 2 LEADERBOARD", "REVERSED"};
        draw_txtbox(&title);

        // Draw grid of buttons
        for (int i = 0; i < n_levels; i++) {
            int row = i / cols;
            int col = i % cols;
            int x = start_x + col * (btn_width + h_spacing);
            int y = start_y + row * (btn_height + v_spacing);
            Button btn = {x, y, btn_width, btn_height, (char*)level_names[i]};
            if (i == selected) {
                attron(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            }
            draw_btn(&btn);
            if (i == selected) {
                attroff(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            }
        }

        mvprintw(start_y - 2, start_x, "Gunakan panah untuk navigasi, ESC untuk kembali");
        refresh();

        switch (ch) {
            case KEY_UP: {
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                int row = selected / cols;
                int col = selected % cols;
                if (row > 0) {
                    int above = selected - cols;
                    if (above < n_levels) selected = above;
                }
                break;
            }
            case KEY_DOWN: {
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                int row = selected / cols;
                int col = selected % cols;
                int below = selected + cols;
                if (below < n_levels) {
                    selected = below;
                } else {
                    // If last row is incomplete, stay in same column if possible
                    int last_row_start = (rows - 1) * cols;
                    int last_row_end = n_levels - 1;
                    int new_idx = last_row_start + col;
                    if (new_idx <= last_row_end) selected = new_idx;
                }
                break;
            }
            case KEY_LEFT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if (selected % cols > 0) selected--;
                break;
            case KEY_RIGHT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if ((selected % cols) < (cols - 1) && selected + 1 < n_levels) selected++;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                break;
            default:
                break;
        }
    }
}

void ch3_leaderboard() {
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
    int cols = 5; // 5 columns for 18 levels (last row will have 3)
    int rows = (n_levels + cols - 1) / cols;
    int btn_width = COLS / (cols + 1); // leave some margin
    int btn_height = 3;
    int h_spacing = 2;
    int v_spacing = 1;
    int grid_width = cols * btn_width + (cols - 1) * h_spacing;
    int grid_height = rows * btn_height + (rows - 1) * v_spacing;
    int start_x = (COLS - grid_width) / 2;
    int start_y = LINES / 2 - grid_height / 2;

    while ((ch = getch()) != 27) { // ESC to exit
        clear();
        handle_resize(&prev_lines, &prev_cols);
        Txtbox title = {COLS/2 - 10, 2, strlen("CHAPTER 3 LEADERBOARD") + 5, 2, "CHAPTER 3 LEADERBOARD", "REVERSED"};
        draw_txtbox(&title);

        // Draw grid of buttons
        for (int i = 0; i < n_levels; i++) {
            int row = i / cols;
            int col = i % cols;
            int x = start_x + col * (btn_width + h_spacing);
            int y = start_y + row * (btn_height + v_spacing);
            Button btn = {x, y, btn_width, btn_height, (char*)level_names[i]};
            if (i == selected) {
                attron(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            }
            draw_btn(&btn);
            if (i == selected) {
                attroff(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            }
        }

        mvprintw(start_y - 2, start_x, "Gunakan panah untuk navigasi, ESC untuk kembali");
        refresh();

        switch (ch) {
            case KEY_UP: {
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                int row = selected / cols;
                int col = selected % cols;
                if (row > 0) {
                    int above = selected - cols;
                    if (above < n_levels) selected = above;
                }
                break;
            }
            case KEY_DOWN: {
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                int row = selected / cols;
                int col = selected % cols;
                int below = selected + cols;
                if (below < n_levels) {
                    selected = below;
                } else {
                    // If last row is incomplete, stay in same column if possible
                    int last_row_start = (rows - 1) * cols;
                    int last_row_end = n_levels - 1;
                    int new_idx = last_row_start + col;
                    if (new_idx <= last_row_end) selected = new_idx;
                }
                break;
            }
            case KEY_LEFT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if (selected % cols > 0) selected--;
                break;
            case KEY_RIGHT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if ((selected % cols) < (cols - 1) && selected + 1 < n_levels) selected++;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                break;
            default:
                break;
        }
    }
}

void ch4_leaderboard() {
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
    int cols = 5; // 5 columns for 21 levels (last row will have 1)
    int rows = (n_levels + cols - 1) / cols;
    int btn_width = COLS / (cols + 1); // leave some margin
    int btn_height = 3;
    int h_spacing = 2;
    int v_spacing = 1;
    int grid_width = cols * btn_width + (cols - 1) * h_spacing;
    int grid_height = rows * btn_height + (rows - 1) * v_spacing;
    int start_x = (COLS - grid_width) / 2;
    int start_y = LINES / 2 - grid_height / 2;

    while ((ch = getch()) != 27) { // ESC to exit
        clear();
        handle_resize(&prev_lines, &prev_cols);
        Txtbox title = {COLS/2 - 10, 2, strlen("CHAPTER 4 LEADERBOARD") + 5, 2, "CHAPTER 4 LEADERBOARD", "REVERSED"};
        draw_txtbox(&title);

        // Draw grid of buttons
        for (int i = 0; i < n_levels; i++) {
            int row = i / cols;
            int col = i % cols;
            int x = start_x + col * (btn_width + h_spacing);
            int y = start_y + row * (btn_height + v_spacing);
            Button btn = {x, y, btn_width, btn_height, (char*)level_names[i]};
            if (i == selected) {
                attron(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            }
            draw_btn(&btn);
            if (i == selected) {
                attroff(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            }
        }

        mvprintw(start_y - 2, start_x, "Gunakan panah untuk navigasi, ESC untuk kembali");
        refresh();

        switch (ch) {
            case KEY_UP: {
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                int row = selected / cols;
                int col = selected % cols;
                if (row > 0) {
                    int above = selected - cols;
                    if (above < n_levels) selected = above;
                }
                break;
            }
            case KEY_DOWN: {
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                int row = selected / cols;
                int col = selected % cols;
                int below = selected + cols;
                if (below < n_levels) {
                    selected = below;
                } else {
                    // If last row is incomplete, stay in same column if possible
                    int last_row_start = (rows - 1) * cols;
                    int last_row_end = n_levels - 1;
                    int new_idx = last_row_start + col;
                    if (new_idx <= last_row_end) selected = new_idx;
                }
                break;
            }
            case KEY_LEFT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if (selected % cols > 0) selected--;
                break;
            case KEY_RIGHT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if ((selected % cols) < (cols - 1) && selected + 1 < n_levels) selected++;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                break;
            default:
                break;
        }
    }
}

void ch5_leaderboard() {
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
    int cols = 6; // 6 columns for 24 levels (last row will have 4)
    int rows = (n_levels + cols - 1) / cols;
    int btn_width = COLS / (cols + 1); // leave some margin
    int btn_height = 3;
    int h_spacing = 2;
    int v_spacing = 1;
    int grid_width = cols * btn_width + (cols - 1) * h_spacing;
    int grid_height = rows * btn_height + (rows - 1) * v_spacing;
    int start_x = (COLS - grid_width) / 2;
    int start_y = LINES / 2 - grid_height / 2;

    while ((ch = getch()) != 27) { // ESC to exit
        clear();
        handle_resize(&prev_lines, &prev_cols);
        Txtbox title = {COLS/2 - 10, 2, strlen("CHAPTER 5 LEADERBOARD") + 5, 2, "CHAPTER 5 LEADERBOARD", "REVERSED"};
        draw_txtbox(&title);

        // Draw grid of buttons
        for (int i = 0; i < n_levels; i++) {
            int row = i / cols;
            int col = i % cols;
            int x = start_x + col * (btn_width + h_spacing);
            int y = start_y + row * (btn_height + v_spacing);
            Button btn = {x, y, btn_width, btn_height, (char*)level_names[i]};
            if (i == selected) {
                attron(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            }
            draw_btn(&btn);
            if (i == selected) {
                attroff(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            }
        }

        mvprintw(start_y - 2, start_x, "Gunakan panah untuk navigasi, ESC untuk kembali");
        refresh();

        switch (ch) {
            case KEY_UP: {
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                int row = selected / cols;
                int col = selected % cols;
                if (row > 0) {
                    int above = selected - cols;
                    if (above < n_levels) selected = above;
                }
                break;
            }
            case KEY_DOWN: {
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                int row = selected / cols;
                int col = selected % cols;
                int below = selected + cols;
                if (below < n_levels) {
                    selected = below;
                } else {
                    // If last row is incomplete, stay in same column if possible
                    int last_row_start = (rows - 1) * cols;
                    int last_row_end = n_levels - 1;
                    int new_idx = last_row_start + col;
                    if (new_idx <= last_row_end) selected = new_idx;
                }
                break;
            }
            case KEY_LEFT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if (selected % cols > 0) selected--;
                break;
            case KEY_RIGHT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if ((selected % cols) < (cols - 1) && selected + 1 < n_levels) selected++;
                break;
            case '\n':
            case KEY_ENTER:
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                break;
            default:
                break;
        }
    }
}