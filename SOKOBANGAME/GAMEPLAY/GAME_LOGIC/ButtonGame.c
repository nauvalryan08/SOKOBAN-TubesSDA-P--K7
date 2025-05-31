#include "ButtonGame.h"

//======================//
//==>  RESET BUTTON  <==//
//======================//
/* {Sopian} */

void reset_game(RoomLayout *room, const char **map, Cur_Level Level) {
    Level(room);
}

boolean is_reset_pressed(int ch) {
    return (ch == 'r' || ch == 'R');
}

//=======================================================================//
//== Method untuk menerima input KEY ARROW dan menjalankan pemeriksaan ==//
//=======================================================================//
/* {Sopian} */

void handle_input (RoomLayout *room, const char **map, Cur_Level Level) {
    int ch = getch();

    switch (ch) {
        case KEY_UP :
            move_player(room, 0, -1, map);
            break;
        case KEY_DOWN :
            move_player(room, 0, +1, map);
            break;
        case KEY_LEFT :
            move_player(room, -1, 0, map);
            break;
        case KEY_RIGHT :
            move_player(room, +1, 0, map);
            break;
        case 'r' :
        case 'R' :
            reset_game(room, map, Level);
            break;
    }
}