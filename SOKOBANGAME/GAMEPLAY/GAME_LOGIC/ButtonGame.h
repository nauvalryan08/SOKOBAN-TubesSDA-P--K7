#ifndef BUTTONGAME_H
#define BUTTONGAME_H

#include "../../UTILS/include/boolean.h"
#include "../../UTILS/include/curses.h"
#include "../../VIEW/viewtoolkit.h"
#include "../../VIEW/chapterscreen.h"

#include "../ARENA_LOGIC/RoomFactory.h"
#include "../ARENA_LOGIC/Level.h"
#include "GameLogic.h"
#include "UndoGame.h"
#include "../REPLAY_LOGIC/ReplayGame.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//======================//
//==>  RESET BUTTON  <==//
//======================//
/* {Sopian} */
boolean is_reset_pressed(int ch);

//=====================//
//==>  Undo BUTTON  <==//
//=====================//
/* {Sopian} */
boolean is_Undo_pressed(int ch);

//=======================================================================//
//== Method untuk menerima input KEY ARROW dan menjalankan pemeriksaan ==//
//=======================================================================//
/* {Sopian} */
void handle_input (RoomLayout *room, const char **map, Stack *StackUndo, Queue *hintQueue, int *keyOutput, Button *quit);

#endif