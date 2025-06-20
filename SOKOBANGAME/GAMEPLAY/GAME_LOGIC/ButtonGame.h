#ifndef BUTTONGAME_H
#define BUTTONGAME_H

#include "../../UTILS/include/boolean.h"
#include "../../UTILS/include/curses.h"
#include "../../UTILS/sound/soundmanager.h"
#include "../../UTILS/validator/validator.h"

#include "../../VIEW/viewtoolkit.h"
#include "../../VIEW/chapterscreen.h"

#include "../ARENA_LOGIC/RoomFactory.h"
#include "../ARENA_LOGIC/Level.h"
#include "../UNDO_LOGIC/UndoGame.h"
#include "GameLogic.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

//======================//
//==>  RESET BUTTON  <==//
//======================//
/* {Sopian} */
Boolean is_reset_pressed(int ch);

//=====================//
//==>  Undo BUTTON  <==//
//=====================//
/* {Sopian} */
Boolean is_Undo_pressed(int ch);

//=======================================================================//
//== Method untuk menerima input KEY ARROW dan menjalankan pemeriksaan ==//
//=======================================================================//
/* {Sopian} */
void handle_input (RoomLayout *room, const char **map, Stack *StackUndo, Queue *ReplayQueue, int *keyOutput, Button *quit, const char *username);

#endif