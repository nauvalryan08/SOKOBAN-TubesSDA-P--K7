#include "sokoban.h"

int main() {

    setlocale(LC_ALL, "");

    initscr();
    
    //inisiasi warna
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    cbreak();               //input tanpa ENTER
    noecho();               // Input tanpa melihatkan karakter
    curs_set(FALSE);        //curs_set nonaktif
    keypad(stdscr, TRUE);   //mengaktifkan input ENTER,f1,f11, ARROW, dll
    timeout(0);

    RoomLayout room;
    start_level(&room, Level_1c4_map, Level_1c4);

    getch();
    endwin();
    return 0;
}
