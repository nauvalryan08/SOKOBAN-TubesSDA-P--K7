#define NCURSES_MOUSE_VERSION
#include "lobbyaltscreen.h"

void print_alt_title() {
    // ASCII art title split into lines
char *title[] = {
        "                                                                      \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                                                                                ",
        "                                         \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB              \xDB\xDB\xDB\xDB   \xDB\xDB      \xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB      \xDB\xDB",
        "                                       \xDB\xDB\xDB\xDB      \xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB   \xDB\xDB      \xDB\xDB  \xDB\xDB    @ \xFE . . \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB\xDB\xDB    \xDB\xDB",
        "                                       \xDB\xDB            \xDB\xDB\xDB\xDB          \xDB\xDB\xDB\xDB  \xDB\xDB   \xDB\xDB    \xDB\xDB    \xDB\xDB            \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB\xDB\xDB    \xDB\xDB",
        "                                       \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB  \xDB\xDB   \xDB\xDB  \xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB  \xDB\xDB  \xDB\xDB",
        "                                                 \xDB\xDB  \xDB\xDB    \xDB\xDB  \xDB\xDB    \xDB\xDB  \xDB\xDB   \xDB\xDB\xDB\xDB        \xDB\xDB            \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB  \xDB\xDB  \xDB\xDB",
        "                                                 \xDB\xDB  \xDB\xDB      \xDB\xDB      \xDB\xDB  \xDB\xDB   \xDB\xDB  \xDB\xDB      \xDB\xDB\xDB\xDB\xDB\xDB        \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB    \xDB\xDB\xDB\xDB",
        "                                                 \xDB\xDB  \xDB\xDB    \xDB\xDB  \xDB\xDB    \xDB\xDB  \xDB\xDB   \xDB\xDB    \xDB\xDB    \xDB\xDB  \xFE     \xDB\xDB  \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB    \xDB\xDB\xDB\xDB",
        "                                       \xDB\xDB      \xDB\xDB\xDB\xDB  \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB  \xDB\xDB   \xDB\xDB      \xDB\xDB  \xDB\xDB        \xDB\xDB  \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB      \xDB\xDB  \xDB\xDB      \xDB\xDB",
        "                                       \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB\xDB\xDB          \xDB\xDB\xDB\xDB\xDB\xDB     \xDB\xDB      \xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB  \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB    \xDB\xDB      \xDB\xDB  \xDB\xDB      \xDB\xDB",
        "                                                     \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB                                                                       "
    };
    int title_lines = 11;

    // Center and print each line
    for (int i = 0; i < title_lines; i++) {
        int len = strlen(title[i]);
        int x_pos = (COLS - len) / 2;
        if (x_pos < 0) {
            // If terminal is too small, show what fits
            mvprintw(2 + i, 0, "%.*s", COLS, title[i]);
        } else {
            mvprintw(2 + i, x_pos, "%s", title[i]);
        }
    }
}

int show_alt_menu(int selected, int items, Button *btnset){
    draw_box(1, 1, 35, LINES-2);
    
    Txtbox Small_title = {3,2,31,6,"===SOKOBAN===", "REVERSE"};
    attron(COLOR_PAIR(COLOR_YELLOW));
    draw_txtbox(&Small_title);
    attroff(COLOR_PAIR(COLOR_YELLOW));
    for (int i = 0; i < items; i++) {
        if (i == selected) {
            attron(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
        }
        draw_btn(&btnset[i]);
        if (i == selected) {
            attroff(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
        }
    }
    attron(COLOR_PAIR(COLOR_YELLOW));
    mvprintw(LINES-6, 3, "Klik Kiri untuk memilih menu");
    mvprintw(LINES-5, 3, "Atau gunakan tombol panah");
    mvprintw(LINES-4, 3, "Untuk navigasi.");
    mvprintw(LINES-3, 3, "Tekan ENTER untuk memilih");
    attroff(COLOR_PAIR(COLOR_YELLOW));
}

int show_alt_lobby(){
    Button menu_items[] = {{3,LINES/2 - 14, 31, 4, "PLAY GAME"},
                            {3,LINES/2 - 9, 31, 4, "HISTORY"},
                            {3,LINES/2 - 4, 31, 4, "LEADERBOARD"},
                            {3,LINES/2 + 1, 31, 4, "HOW TO PLAY"},
                            {3,LINES/2 + 6, 31, 4, "QUIT GAME"}};
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    int ch;
    int prev_lines = LINES;
    int prev_cols = COLS;
    mmask_t old;
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, &old);
    MEVENT event;
    int items = 5;
    int selected = 0;
   

    while (1) {
        clear();
        handle_resize(&prev_lines, &prev_cols);
        
        attron(COLOR_PAIR(1) | A_BOLD);
        print_alt_title();
        attroff(COLOR_PAIR(1) | A_BOLD);
        show_alt_menu(selected, 5, menu_items);
            ch = getch();
            switch (ch) {
                case KEY_UP:
                    selected = (selected > 0) ? selected - 1 : items - 1;
                    break;
                case KEY_DOWN:
                    selected = (selected < items - 1) ? selected + 1 : 0;
                    break;
                case KEY_MOUSE:
                    if (getmouse(&event) == OK) {
                        if (event.bstate & BUTTON1_CLICKED) {
                            for (int i = 0; i < items; i++) {
                                if (isbtnarea(&menu_items[i], event.x, event.y)) {
                                    selected = i;
                                }
                            }
                        }
                        else if (event.bstate & BUTTON1_DOUBLE_CLICKED) {
                        for (int i = 0; i < items; i++) {
                            if (isbtnarea(&menu_items[i], event.x, event.y)) {
                                selected = i;
                                switch(selected) {
                                    case 0: return 1;
                                    case 1: return 2;
                                    case 2: return 3;
                                    case 3: return 4;
                                    case 4: return 5;
                                }
                            }
                        }
                    }
                }
                    break;
                case '\n':
                case KEY_ENTER:
                    if (selected >= 0 && selected < items) {
                        switch(selected) {
                            case 0: // PLAY GAME
                                return 1;
                            case 1: // HISTORY
                                return 2;
                            case 2: // LEADERBOARD
                                return 3;
                            case 3: // HOW TO PLAY
                                return 4;
                            case 4: // QUIT GAME
                                return 5;
                        }
                    }
                    break;
                case KEY_RESIZE:
                    resize_term(0,0);
                    break;
                default:
                    break;
            }
    refresh();
    }
}