#include <curses.h>
#include "ARENA_LOGIC/Level.h"
#include "ARENA_LOGIC/RoomFactory.h"

int main() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    RoomLayout room;
    Level_1c2(&room);                    // dari level.c
    print_room(Level_1c2_map, &room);    // cetak peta & objek

    getch();
    endwin();
    return 0;
}
