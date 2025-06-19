#include "UndoGame.h"


//=====================//
//==>  UNDO LOGIC  <==//
//=====================//
/* {Sopian} */

void save_state(GameUndo *prevMove, const RoomLayout *room) {
    RoomLayout *roomCopy = (RoomLayout*)malloc(sizeof(RoomLayout));
    if (!roomCopy) return;
    //coppy data room ke roomcopy
    memcpy(roomCopy, room, sizeof(RoomLayout));
    //push memory ke stack
    stack_push(prevMove, roomCopy);
}

void undo_game(GameUndo *prevMove, RoomLayout *currRoom) {
    if (stack_isEmpty(prevMove)) {
        printw("Undo Failed: stack empty");   
        return;
    }

    //pop data dari stack
    RoomLayout *poppedRoom = (RoomLayout*)stack_pop(prevMove);
    // salin data ke currRoom untuk dikembalikan
    memcpy(currRoom, poppedRoom, sizeof(RoomLayout));
    printw("Undo berhasil");
    //free memory;
    free(poppedRoom);
};