#ifndef LEVEL_H
#define LEVEL_H

#include "RoomFactory.h"

typedef struct {
    const char *level_id;           //Untuk traversal dan searching
    const char *level_name;         //Display name saat runtime
    const char **map;               //Map level
    boolean is_unlcoked;            //Status unlocked
    boolean is_finished;            //Status pernah diselesaikan
}LevelData;


typedef enum {
    LEVEL_1C1,
    LEVEL_1C2,
    LEVEL_1C3,
    LEVEL_1C4,
    LEVEL_1C5,
    LEVEL_1C6,
    LEVEL_1C7,
    LEVEL_1C8,
    LEVEL_COUNT
}LevelID;

extern LevelData ALL_LEVELS[LEVEL_COUNT];

//============================================//
//==> MODUL Definisi ARENA DAN LEVEL-LEVEL <==//
//============================================//
/* {Sopian} */

extern const char *Level_1c1_map[];

extern const char *Level_1c2_map[];

extern const char *Level_1c3_map[];

extern const char *Level_1c4_map[];

extern const char *Level_1c5_map[];

extern const char *Level_1c6_map[];

extern const char *Level_1c7_map[];

extern const char *Level_1c8_map[];


//==============================================//
//==> MODUL MANAGEMENT ARENA DAN LEVEL-LEVEL <==//
//==============================================//
/* {Sopian} */

LevelData* get_level_by_id(const char* level_id);


#endif