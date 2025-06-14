#ifndef REPLAYGAME_H
#define REPLAYGAME_H

#include "../../DATABASE/DatabasePath.h"

#include "../ARENA_LOGIC/RoomFactory.h"
#include "../../STRUCTURES/queue.h"
#include "../../STRUCTURES/stack.h"
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

typedef struct {
    char move; // 'U','D','L','R','Z'
} ReplayStep;

//=========================//
//==>  DATABASE ACCESS  <==//
//=========================//

void saveReplayForUser(Queue *q, const char *user);
Boolean loadReplayRecord(Queue *q, const char *username, const char *dataID);

//=========================//
//==>      INITIATOR    <==//
//=========================//

void initReplayQueue(Queue *q);

ReplayStep *createStep (char Move);

void clearReplayQueue(Queue *q);

//=========================//
//==>  REPLAY COMANDER  <==//
//=========================//

void playReplay(RoomLayout *room, LevelData level, Queue *q);

#endif