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
    char ID_level[20];
    int ID_data;
    RoomLayout room;
} SaveState;

//==> struct definision
typedef struct {
    char* username;
    char ID_level[20];
    int ID_data;
    ScoreData scoreData;
    ReplayStep *replay_data;
}PlayData;


//=================================================//
//==                DATABASE ACCESS              ==//
//=================================================//
/* {Sopian} */

//==> Memnyimpan Hasil data usai bermain
void save_data_to_database(const char* username, const char* ID_level, int ID_data, ScoreData scoreData, Queue *replayQueue);

// ==> Load Data play berdasarakn ID
Boolean load_play_data_by_id(const char* username, int ID_data, ScoreData* out, Queue* replay);

//==> menyimpan State permainan saat Exit [untuk kembali dilanjutkan saat bermain lagi]
void save_game_state(const char* username, const char* ID_level, int ID_data, RoomLayout* room);

//==> Load gameState (mengambil data RoomLayout untuk nanti dijadikan aacuan start game)
int load_game_state(const char* username, const char* ID_level, SaveState* outSave);

//===> menghapus game state pada database yang sudah dipakai
void remove_game_state_entry(const char* username, const char* ID_level, int ID_data);


// ================== //
// ->     TEMP PATH   //
//====================//

void save_temp_play_data(const char* username, const char* ID_level, int ID_data, ScoreData scoreData, Queue* replayQueue);

Boolean load_temp_play_data(const char* username, int ID_data, ScoreData* out, Queue* replay);

void remove_temp_play_data_entry(const char* username, int ID_data, const char* ID_level);


#endif