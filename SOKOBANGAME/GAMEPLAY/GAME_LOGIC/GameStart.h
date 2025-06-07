#ifndef GAMESTART_H
#define GAMESTART_H

#include "../../UTILS/include/boolean.h"
#include "../../UTILS/include/curses.h"

#include "../ARENA_LOGIC/RoomFactory.h"
#include "../ARENA_LOGIC/Level.h"
#include "GameLogic.h"
#include "ButtonGame.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//==========================================================//
//== Method untuk menjalankan Level berdasarkan Parameter ==//
//==========================================================//
/* {Sopian} */
void start_level (RoomLayout *room, LevelData *level);


#endif