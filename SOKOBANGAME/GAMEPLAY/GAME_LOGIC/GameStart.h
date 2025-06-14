#ifndef GAMESTART_H
#define GAMESTART_H

#include "../../DATABASE/DatabasePath.h"

#include "../../UTILS/include/boolean.h"
#include "../../UTILS/include/curses.h"
#include "../../VIEW/viewtoolkit.h"

#include "../ARENA_LOGIC/RoomFactory.h"
#include "../ARENA_LOGIC/Level.h"
#include "../ARENA_LOGIC/ChapterManager.h"
#include "../REPLAY_LOGIC/ReplayGame.h"

#include "../../STRUCTURES/queue.h"
#include "GameLogic.h"
#include "ButtonGame.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

//==========================================================//
//== Method untuk menjalankan Level berdasarkan Parameter ==//
//==========================================================//
/* {Sopian} */
void start_level (RoomLayout *room, LevelData *level, ChapterData * current_chapter, const char *username);

void game_finished(RoomLayout *room, LevelData *level, ChapterData *current_chapter, Queue *replayQueue, ScoreData scoreData, const char *username);


//=================================================//
//==                DATABASE ACCESS              ==//
//=================================================//
/* {Sopian} */
void saveDataToDatabase ( Queue *q, const char *username, const char *levelID, const char *dataID, ScoreData scoreData);



#endif