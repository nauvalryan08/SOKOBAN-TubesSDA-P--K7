#define NCURSES_MOUSE_VERSION
#include "ButtonGame.h"

//======================//
//==>  RESET BUTTON  <==//
//======================//
/* {Sopian} */
Boolean is_reset_pressed(int ch) {
    return (ch == 'r' || ch == 'R');
}


//=====================//
//==>  Undo BUTTON  <==//
//=====================//
/* {Sopian} */
Boolean is_Undo_pressed(int ch) {
    return (ch == 'u' || ch == 'U');
}


//=======================================================================//
//== Method untuk menerima input KEY ARROW dan menjalankan pemeriksaan ==//
//=======================================================================//
/* {Sopian} */

void handle_input (RoomLayout *room, const char **map, Stack *UndoStack, Queue *ReplayQueue, int *keyOutput, Button *btn, const char *username) {
    int ch = getch();
    MEVENT event;
    mmask_t old;
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, &old);
    Boolean valid = false;

    switch (ch) {
        case KEY_UP :
            save_state(UndoStack, room);
            valid = move_player(room, 0, -1, map);
            if (!valid) {
                undo_game(UndoStack, room);     //Memastikan tidak menyimpan data undo utnuk gerakan tidak valid 
            } else {
                ReplayStep* step = createStep('U');
                enqueue(ReplayQueue, step);
            }
            break;
        case KEY_DOWN :
            save_state(UndoStack, room);
            valid = move_player(room, 0, +1, map);
            if (!valid) {
                undo_game(UndoStack, room);     //Memastikan tidak menyimpan data undo utnuk gerakan tidak valid 
            } else {
                ReplayStep* step = createStep('D');
                enqueue(ReplayQueue, step);
            }
            break;
        case KEY_LEFT :
            save_state(UndoStack, room);
            valid = move_player(room, -1, 0, map);
            if (!valid) {
                undo_game(UndoStack, room);     //Memastikan tidak menyimpan data undo utnuk gerakan tidak valid 
            } else {
                ReplayStep* step = createStep('L');
                enqueue(ReplayQueue, step);
            }
            break;
        case KEY_RIGHT :
            save_state(UndoStack, room);
            valid = move_player(room, +1, 0, map);
            if (!valid) {
                undo_game(UndoStack, room);     //Memastikan tidak menyimpan data undo utnuk gerakan tidak valid 
            } else {
                ReplayStep* step = createStep('R');
                enqueue(ReplayQueue, step);
            }
            break;
        case 'r' :
        case 'R' :
            reset_game(room, map);
            stack_clear(UndoStack);
            clearQueue(ReplayQueue);
            break;
        case 'u' :
        case 'U' :
            undo_game(UndoStack, room);
            ReplayStep* step = createStep('Z');
            enqueue(ReplayQueue, step);
            break;
        case 27:
            *keyOutput = 27;
            break;
        case 'F' :
            room->finish.is_activated = true;
            *keyOutput = 'F';
            break;
        
        case KEY_MOUSE:
        // Handle Quit Button
        if (getmouse(&event) == OK) {
            if (event.bstate & BUTTON1_CLICKED){
                if (isbtnarea(btn, event.x, event.y)) {
                    *keyOutput = 27;
                    print_chapter_screen(username);
                }
            }
        }
        break;
    }
}