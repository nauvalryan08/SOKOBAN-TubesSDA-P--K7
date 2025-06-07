#ifndef REPLAYGAME_H
#define REPLAYGAME_H

#include "../ARENA_LOGIC/RoomFactory.h"
#include "../../STRUCTURES/queue.h"
#include "../GAME_LOGIC/ButtonGame.h"


//=========================//
//==>  DEFINISI STRUCT  <==//
//=========================//

#define MAX_QUEUE 10000
#define MAX_WIDTH 100
#define MAX_HEIGHT 100
#define MAX_QUEUE 10000
#define MAX_STACK 1000
#define MAX_NAME 100
#define REPLAY_FILE "replay_database.txt"

typedef struct {
    char move; // 'U','D','L','R','Z'
} ReplayStep;

//=========================//
//==>  DATABASE ACCESS  <==//
//=========================//

void saveReplayForUser(Queue *q, const char *user);
boolean loadReplayForUser(Queue *q, const char *user);


//=========================//
//==>      INITIATOR    <==//
//=========================//

void initReplayQueue(Queue *q);

ReplayStep *createStep (char Move);


//=========================//
//==>  REPLAY COMANDER  <==//
//=========================//

void playReplay(RoomLayout *room, LevelData level, Queue *q);




#endif