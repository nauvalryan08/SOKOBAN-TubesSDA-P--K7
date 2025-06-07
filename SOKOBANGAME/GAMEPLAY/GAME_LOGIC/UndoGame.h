#ifndef UNDOGAME_H
#define UNDOGAME_H

#include "../../STRUCTURES/stack.h"
#include "../ARENA_LOGIC/RoomFactory.h"

//================================//
//==>  STRUCT OBJECT & LAYOUT  <==//
//================================//
/* {Sopian} */

typedef Stack GameUndo;

//=====================//
//==>  UNDO LOGIC  <==//
//=====================//
/* {Sopian} */
void save_state(GameUndo *prevMove, const RoomLayout *room);

void undo_game(GameUndo *prevMove, RoomLayout *currRoom);

#endif