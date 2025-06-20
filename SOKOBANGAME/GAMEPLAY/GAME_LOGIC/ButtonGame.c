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

    pthread_t soundThread;
    
    switch (ch) {
        case KEY_UP :
            pthread_create(&soundThread, NULL, playMoveSound, NULL);
            pthread_detach(soundThread);
            save_state(UndoStack, room);
            valid = move_player(room, 0, -1, map);
            if (!valid) {
                undo_game(UndoStack, room);     //Memastikan tidak menyimpan data undo utnuk gerakan tidak valid 
            } else {
                ReplayStep* step = createStep('U');
                enqueue(ReplayQueue, step);
                *keyOutput = 1;     //Indikasi menekan move button
            }
            break;
        case KEY_DOWN :
            pthread_create(&soundThread, NULL, playMoveSound, NULL);
            pthread_detach(soundThread);
            save_state(UndoStack, room);
            valid = move_player(room, 0, +1, map);
            if (!valid) {
                undo_game(UndoStack, room);     //Memastikan tidak menyimpan data undo utnuk gerakan tidak valid 
            } else {
                ReplayStep* step = createStep('D');
                enqueue(ReplayQueue, step);
                *keyOutput = 1;     //Indikasi menekan move button
            }
            break;
        case KEY_LEFT :
            pthread_create(&soundThread, NULL, playMoveSound, NULL);
            pthread_detach(soundThread);
            save_state(UndoStack, room);
            valid = move_player(room, -1, 0, map);
            if (!valid) {
                undo_game(UndoStack, room);     //Memastikan tidak menyimpan data undo utnuk gerakan tidak valid 
            } else {
                ReplayStep* step = createStep('L');
                enqueue(ReplayQueue, step);
                *keyOutput = 1;     //Indikasi menekan move button
            }
            break;
        case KEY_RIGHT :
            pthread_create(&soundThread, NULL, playMoveSound, NULL);
            pthread_detach(soundThread);
            save_state(UndoStack, room);
            valid = move_player(room, +1, 0, map);
            if (!valid) {
                undo_game(UndoStack, room);     //Memastikan tidak menyimpan data undo utnuk gerakan tidak valid 
            } else {
                ReplayStep* step = createStep('R');
                enqueue(ReplayQueue, step);
                *keyOutput = 1;     //Indikasi menekan move button
            }
            break;
        case 'r' :
        case 'R' :
            if (validate_GameReset()) {
                pthread_create(&soundThread, NULL, playGameResetSound, NULL);
                pthread_join(soundThread, NULL);
                reset_game(room, map);
                stack_clear(UndoStack);
                clearQueue(ReplayQueue);
                showMsg_GameReset();
                *keyOutput = 'R';
            }
            break;
        case 'u' :
        case 'U' :
            undo_game(UndoStack, room);
            pthread_create(&soundThread, NULL, playUndoSound, NULL);
            pthread_detach(soundThread);
            ReplayStep* step = createStep('Z');
            enqueue(ReplayQueue, step);
            *keyOutput = 'U';     //indikasi Undo
            break;
        case 27:
            *keyOutput = 27;
            break;
        case 'F' :
            room->finish.is_activated = true;
            *keyOutput = 'F';
            // if (validate_CheatGame()) {
            //     showMsg_CheatGame(); getchar();
            //     room->finish.is_activated = true;
            //     *keyOutput = 'F';
            // }
            break;
        
        case KEY_MOUSE:
        // Handle Quit Button
        if (getmouse(&event) == OK) {
            if (event.bstate & BUTTON1_CLICKED){
                pthread_create(&soundThread, NULL, playEnterSound, NULL);
                pthread_join(soundThread, NULL);
                if (isbtnarea(btn, event.x, event.y)) {
                    *keyOutput = 27;
                }
            }
        }
        break;
    }
}