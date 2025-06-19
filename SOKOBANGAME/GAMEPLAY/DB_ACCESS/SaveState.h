#ifndef SAVESTATE_H
#define SAVESTATE_H

#include "../../STRUCTURES/queue.h"
#include "../../DATABASE/DatabasePath.h"
#include "../REPLAY_LOGIC/ReplayGame.h"


//=======================================================//
//== Struct SaveData untuk menyimpan data state player ==//
//=======================================================//
/* {Sopian} */

typedef struct {
    char username[20];
    char level_id[16];
    RoomLayout room;
} SaveState;


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