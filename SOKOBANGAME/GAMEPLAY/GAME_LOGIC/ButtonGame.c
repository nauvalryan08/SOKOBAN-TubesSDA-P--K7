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

void handle_input (RoomLayout *room, const char **map, Stack *UndoStack) {
    int ch = getch();
    boolean valid = false;

    switch (ch) {
        case KEY_UP :
            save_state(UndoStack, room);
            valid = move_player(room, 0, -1, map);
            if (!valid) {
                undo_game(UndoStack, room);     //Memastikan tidak menyimpan data undo utnuk gerakan tidak valid 
            }
            break;
        case KEY_DOWN :
            save_state(UndoStack, room);
            valid = move_player(room, 0, +1, map);
            if (!valid) {
                undo_game(UndoStack, room);     //Memastikan tidak menyimpan data undo utnuk gerakan tidak valid 
            }
            break;
        case KEY_LEFT :
            save_state(UndoStack, room);
            valid = move_player(room, -1, 0, map);
            if (!valid) {
                undo_game(UndoStack, room);     //Memastikan tidak menyimpan data undo utnuk gerakan tidak valid 
            }
            break;
        case KEY_RIGHT :
            save_state(UndoStack, room);
            valid = move_player(room, +1, 0, map);
            if (!valid) {
                undo_game(UndoStack, room);     //Memastikan tidak menyimpan data undo utnuk gerakan tidak valid 
            }
            break;
        case 'r' :
        case 'R' :
            reset_game(room, map);
            break;
        case 'u' :
        case 'U' :
            undo_game(UndoStack, room);
            break;
    }
}