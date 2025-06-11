#ifndef DATAHIERARKI_H
#define DATAHIERARKI_H 

#include "../STRUCTURES/tree.h"
#include "../GAMEPLAY/REPLAY_LOGIC/ReplayGame.h"


//==> struct definision
typedef struct {
    char* usernamae;
    int ID_data;
    int ID_level;
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

boolean compareLevelNameByID(void* data1, void* data2);

//==> Create new Data

PlayData* createPlayData(char* username, int ID_data, int ID_level, int score, int time, int total_move, ReplayStep *replay_data);

void addNewDataToTree(Ptree root, PlayData *data);



#endif