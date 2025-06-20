#ifndef DATAHIERARKI_H
#define DATAHIERARKI_H 

#include "../GAMEPLAY/DB_ACCESS/SaveState.h"
#include "../STRUCTURES/tree.h"

//==> Inisiation

Ptree initDataHierarki();


//==> Converter

char *getLevelIDfromString(const char *levelName);

int convertStringIDtoInt(const char *IDstr);

//===> ID comparing

Boolean compareLevelNameByID(void* data1, void* data2);

//==> Create new Data

PlayData* createPlayData(const char* username, int ID_data, const char* ID_level,
                         int score, int time, int total_move, int total_undo,
                         ReplayStep *replay_data);

void addNewDataToTree(Ptree root, PlayData *data);

#endif