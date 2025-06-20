#ifndef GAMESTART_H
#define GAMESTART_H

#include "../DB_ACCESS/SaveState.h"
#include "../../DATABASE/Player.h"

#include "../../UTILS/include/boolean.h"
#include "../../UTILS/include/curses.h"
#include "../../UTILS/sound/soundmanager.h"
#include "../../UTILS/validator/validator.h"
#include "../../UTILS/auth/authentication.h"
#include "../../VIEW/viewtoolkit.h"

#include "../ARENA_LOGIC/Level.h"
#include "../ARENA_LOGIC/ChapterManager.h"

#include "GameLogic.h"
#include "ButtonGame.h"
#include "ScoreGame.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h> // syntax tolower()

//==========================================================//
//== Method untuk menjalankan Level berdasarkan Parameter ==//
//==========================================================//
/* {Sopian} */
void start_level (RoomLayout *room, LevelData *level, ChapterData * current_chapter, const char *username);

int game_finished(RoomLayout *room, LevelData *level, ChapterData *current_chapter, Queue *replayQueue, ScoreData scoreData, const char *username);

int exit_game(RoomLayout *room, const char *username, const char *ID_level, int ID_data, Queue *replayQueue, ScoreData scoreData);

bool ask_continue_save();

#endif