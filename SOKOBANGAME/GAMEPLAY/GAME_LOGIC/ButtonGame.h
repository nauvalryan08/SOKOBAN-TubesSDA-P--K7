#ifndef BUTTONGAME_H
#define BUTTONGAME_H

#include "../../UTILS/include/boolean.h"
#include "../../UTILS/include/curses.h"

#include "../ARENA_LOGIC/RoomFactory.h"
#include "../ARENA_LOGIC/Level.h"
#include "GameLogic.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef void (*Cur_Level)(RoomLayout*);

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
void handle_input (RoomLayout *room, const char **map, Cur_Level Level, Stack *StackUndo);

#endif