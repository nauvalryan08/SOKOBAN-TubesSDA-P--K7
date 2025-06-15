#ifndef HISTORYSCREEN_H
#define HISTORYSCREEN_H

#include "viewtoolkit.h"
#include "../STRUCTURES/tree.h"
#include "../GAMEPLAY/REPLAY_LOGIC/ReplayGame.h"
#include "../GAMEPLAY\ARENA_LOGIC\ChapterManager.h"
#include "../UTILS/sound/soundmanager.h"

typedef struct {
    ReplayStep ReplayData;
    int time;
    int totalMove;
    int score;
    char * username;
}HistoryData;


//===> Tree History Inisiasi
Ptree initHistoryTree();

void print_choose_chapter();

#endif