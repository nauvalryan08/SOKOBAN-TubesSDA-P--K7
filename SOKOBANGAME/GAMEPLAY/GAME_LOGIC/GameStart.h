#ifndef GAMESTART_H
#define GAMESTART_H

#include "../../DATABASE/DatabasePath.h"
#include "../../DATABASE/Player.h"

#include "../../UTILS/include/boolean.h"
#include "../../UTILS/include/curses.h"
#include "../../UTILS/sound/soundmanager.h"
#include "../../UTILS/validator/validator.h"
#include "../../UTILS/auth/authentication.h"
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
#include <ctype.h> // syntax tolower()


//=======================================================//
//== Struct SaveData untuk menyimpan data state player ==//
//=======================================================//
/* {Sopian} */

typedef struct {
    char username[20];
    char level_id[16];
    RoomLayout room;
} SaveState;

//==========================================================//
//== Method untuk menjalankan Level berdasarkan Parameter ==//
//==========================================================//
/* {Sopian} */
void start_level (RoomLayout *room, LevelData *level, ChapterData * current_chapter, const char *username);

void game_finished(RoomLayout *room, LevelData *level, ChapterData *current_chapter, Queue *replayQueue, ScoreData scoreData, const char *username);

int exit_game(RoomLayout *room, const char *username, const char *level_id);

bool ask_continue_save();

//=================================================//
//==                DATABASE ACCESS              ==//
//=================================================//
/* {Sopian} */

//==> Memnyimpan Hasil data usai bermain
void save_data_to_database ( Queue *q, const char *username, const char *levelID, const char *dataID, ScoreData scoreData);

//==> menyimpan State permainan saat Exit [untuk kembali dilanjutkan saat bermain lagi]
void save_game_state (const char* username, const char* level_id, RoomLayout* room);

//==> Load gameState (mengambil data RoomLayout untuk nanti dijadikan aacuan start game)
int load_game_state (const char* username, const char* level_id, RoomLayout* room);

//===> menghapus game state pada database yang sudah dipakai
void remove_game_state_entry(const char* username, const char* level_id);

#endif