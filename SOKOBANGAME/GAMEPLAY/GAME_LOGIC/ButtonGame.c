#include "ButtonGame.h"

//======================//
//==>  RESET BUTTON  <==//
//======================//
/* {Sopian} */
boolean is_reset_pressed(int ch) {
    return (ch == 'r' || ch == 'R');
}


//=====================//
//==>  Undo BUTTON  <==//
//=====================//
/* {Sopian} */
boolean is_Undo_pressed(int ch) {
    return (ch == 'u' || ch == 'U');
}


//=======================================================================//
//== Method untuk menerima input KEY ARROW dan menjalankan pemeriksaan ==//
//=======================================================================//
/* {Sopian} */

void handle_input (RoomLayout *room, const char **map, Cur_Level Level, Stack *UndoStack) {
    int ch = getch();

    switch (ch) {
        case KEY_UP :
            save_state(UndoStack, room);
            move_player(room, 0, -1, map);
            break;
        case KEY_DOWN :
            save_state(UndoStack, room);
            move_player(room, 0, +1, map);
            break;
        case KEY_LEFT :
            save_state(UndoStack, room);
            move_player(room, -1, 0, map);
            break;
        case KEY_RIGHT :
            save_state(UndoStack, room);
            move_player(room, +1, 0, map);
            break;
        case 'r' :
        case 'R' :
            save_state(UndoStack, room);
            reset_game(room, Level);
            break;
        case 'u' :
        case 'U' :
            undo_game(UndoStack, room);
            break;
    }
}