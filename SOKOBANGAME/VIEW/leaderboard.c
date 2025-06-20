#define NCURSES_MOUSE_VERSION
#include "leaderboard.h"

// Fungsi untuk menampilkan layar leaderboard dan menangani interaksi pengguna
void show_leaderboard(const char username[20]){
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
                        ch1_grid(LEADERBOARD, username);
                        break;
                    case 1: // Chapter 2
                        pthread_create(&enterSound, NULL, playEnterSound, NULL);
                        ch2_grid(LEADERBOARD, username);
                        break;
                    case 2: // Chapter 3
                        pthread_create(&enterSound, NULL, playEnterSound, NULL);
                        ch3_grid(LEADERBOARD, username);
                        break;
                    case 3: // Chapter 4
                        pthread_create(&enterSound, NULL, playEnterSound, NULL);
                        ch4_grid(LEADERBOARD, username);
                        break;
                    case 4: // Chapter 5
                        pthread_create(&enterSound, NULL, playEnterSound, NULL);
                        ch5_grid(LEADERBOARD, username);
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
                                    ch1_grid(LEADERBOARD, username);
                                    break;
                                    case 1: // Chapter 2
                                    ch2_grid(LEADERBOARD, username);
                                    break;
                                    case 2: // Chapter 3
                                    ch3_grid(LEADERBOARD, username);
                                    break;
                                    case 3: // Chapter 4
                                    ch4_grid(LEADERBOARD, username);
                                    break;
                                    case 4: // Chapter 5
                                    ch5_grid(LEADERBOARD, username);
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