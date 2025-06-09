#define NCURSES_MOUSE_VERSION
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

void handle_input (RoomLayout *room, const char **map, Stack *UndoStack, Queue *hintQueue, int *keyOutput, Button *btn) {
    int ch = getch();
    MEVENT event;
    mmask_t old;
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, &old);
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
            stack_clear(UndoStack);
            break;
        case 'u' :
        case 'U' :
            undo_game(UndoStack, room);
            break;
        case 27:
            *keyOutput = 27;
            break;
        case KEY_MOUSE:
        // Handle Quit Button
        if (getmouse(&event) == OK) {
            if (event.bstate & BUTTON1_CLICKED){
                if (isbtnarea(btn, event.x, event.y)) {
                    *keyOutput = 27;
                }
            }
        }
        break;
    }
}