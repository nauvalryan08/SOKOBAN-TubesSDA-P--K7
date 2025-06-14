#ifndef DATAHIERARKI_H
#define DATAHIERARKI_H 

#include "../GAMEPLAY/REPLAY_LOGIC/ReplayGame.h"
#include "../STRUCTURES/tree.h"

//==> struct definision
typedef struct {
    char* usernamae;
    int ID_level;
    int ID_data;
    int score;
    int time;
    int total_move;
    ReplayStep *replay_data;
}PlayData;

//==> Inisiation

Ptree initDataHierarki();


//==> Converter

char *getLevelIDfromString(const char *levelName);

int convertStringIDtoInt(const char *IDstr);

//===> ID comparing

Boolean compareLevelNameByID(void* data1, void* data2);

//==> Create new Data

PlayData* createPlayData(char* username, int ID_data, int ID_level, int score, int time, int total_move, ReplayStep *replay_data);

void addNewDataToTree(Ptree root, PlayData *data);

#endif