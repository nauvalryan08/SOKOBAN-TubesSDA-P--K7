#ifndef LEVEL_H
#define LEVEL_H

#include "RoomFactory.h"

//==> STRUCT LEVEL DATA, [UNTUK TREE CHAPTER NANTI]
typedef struct {
    const char *level_id;           //Untuk traversal dan searching
    const char *level_name;         //Display name saat runtime
    const char **map;               //Map level
    boolean is_unlocked;            //Status unlocked
    boolean is_finished;            //Status pernah diselesaikan
}LevelData;


//==> TYPEDEF INDEKS LEVEL MENGGUNAKAN NAMA LEVEL
typedef enum {
    LEVEL_1T1,
    LEVEL_1T2,
    LEVEL_1T3,
    LEVEL_1T4,

    LEVEL_1C1,
    LEVEL_1C2,
    LEVEL_1C3,
    LEVEL_1C4,
    LEVEL_1C5,
    LEVEL_1C6,
    LEVEL_1C7,
    LEVEL_1C8,

    LEVEL_2C1,
    LEVEL_2C2,
    LEVEL_2C3,
    LEVEL_2C4,
    LEVEL_2C5,
    LEVEL_2C6,
    LEVEL_2C7,
    LEVEL_2C8,
    LEVEL_2C9,
    LEVEL_2C10,
    LEVEL_2C11,
    LEVEL_2C12,
    LEVEL_2C13,
    LEVEL_2C14,
    LEVEL_2C15,

    LEVEL_3C1,
    LEVEL_3C2,
    LEVEL_3C3,
    LEVEL_3C4,
    LEVEL_3C5,
    LEVEL_3C6,
    LEVEL_3C7,
    LEVEL_3C8,
    LEVEL_3C9,
    LEVEL_3C10,
    LEVEL_3C11,
    LEVEL_3C12,
    LEVEL_3C13,
    LEVEL_3C14,
    LEVEL_3C15,
    LEVEL_3C16,
    LEVEL_3C17,
    LEVEL_3C18,

    LEVEL_4C1,
    LEVEL_4C2,
    LEVEL_4C3,
    LEVEL_4C4,
    LEVEL_4C5,
    LEVEL_4C6,
    LEVEL_4C7,
    LEVEL_4C8,
    LEVEL_4C9,
    LEVEL_4C10,
    LEVEL_4C11,
    LEVEL_4C12,
    LEVEL_4C13,
    LEVEL_4C14,
    LEVEL_4C15,
    LEVEL_4C16,
    LEVEL_4C17,
    LEVEL_4C18,
    LEVEL_4C19,
    LEVEL_4C20,
    LEVEL_4C21,

    LEVEL_5C1,
    LEVEL_5C2,
    LEVEL_5C3,
    LEVEL_5C4,
    LEVEL_5C5,
    LEVEL_5C6,
    LEVEL_5C7,
    LEVEL_5C8,
    LEVEL_5C9,
    LEVEL_5C10,
    LEVEL_5C11,
    LEVEL_5C12,
    LEVEL_5C13,
    LEVEL_5C14,
    LEVEL_5C15,
    LEVEL_5C16,
    LEVEL_5C17,
    LEVEL_5C18,
    LEVEL_5C19,
    LEVEL_5C20,
    LEVEL_5C21,
    LEVEL_5C22,

    LEVEL_1B,
    LEVEL_2B,
    LEVEL_3B,
    LEVEL_4B,
    LEVEL_5B,
    LEVEL_6B,
    LEVEL_COUNT
} LevelID;


extern LevelData ALL_LEVELS[LEVEL_COUNT];

//============================================//
//==> MODUL Definisi ARENA DAN LEVEL-LEVEL <==//
//============================================//
/* {Sopian} */

extern const char *Level_1t1_map[];
extern const char *Level_1t2_map[];
extern const char *Level_1t3_map[];
extern const char *Level_1t4_map[];
extern const char *Level_1c1_map[];
extern const char *Level_1c2_map[];
extern const char *Level_1c3_map[];
extern const char *Level_1c4_map[];
extern const char *Level_1c5_map[];
extern const char *Level_1c6_map[];
extern const char *Level_1c7_map[];
extern const char *Level_1c8_map[];

extern const char *Level_2c1_map[];
extern const char *Level_2c2_map[];
extern const char *Level_2c3_map[];
extern const char *Level_2c4_map[];
extern const char *Level_2c5_map[];
extern const char *Level_2c6_map[];
extern const char *Level_2c7_map[];
extern const char *Level_2c8_map[];
extern const char *Level_2c9_map[];
extern const char *Level_2c10_map[];
extern const char *Level_2c11_map[];
extern const char *Level_2c12_map[];
extern const char *Level_2c13_map[];
extern const char *Level_2c14_map[];
extern const char *Level_2c15_map[];

extern const char *Level_3c1_map[];
extern const char *Level_3c2_map[];
extern const char *Level_3c3_map[];
extern const char *Level_3c4_map[];
extern const char *Level_3c5_map[];
extern const char *Level_3c6_map[];
extern const char *Level_3c7_map[];
extern const char *Level_3c8_map[];
extern const char *Level_3c9_map[];
extern const char *Level_3c10_map[];
extern const char *Level_3c11_map[];
extern const char *Level_3c12_map[];
extern const char *Level_3c13_map[];
extern const char *Level_3c14_map[];
extern const char *Level_3c15_map[];
extern const char *Level_3c16_map[];
extern const char *Level_3c17_map[];
extern const char *Level_3c18_map[];


extern const char *Level_4c1_map[];
extern const char *Level_4c2_map[];
extern const char *Level_4c3_map[];
extern const char *Level_4c4_map[];
extern const char *Level_4c5_map[];
extern const char *Level_4c6_map[];
extern const char *Level_4c7_map[];
extern const char *Level_4c8_map[];
extern const char *Level_4c9_map[];
extern const char *Level_4c10_map[];
extern const char *Level_4c11_map[];
extern const char *Level_4c12_map[];
extern const char *Level_4c13_map[];
extern const char *Level_4c14_map[];
extern const char *Level_4c15_map[];
extern const char *Level_4c16_map[];
extern const char *Level_4c17_map[];
extern const char *Level_4c18_map[];
extern const char *Level_4c19_map[];
extern const char *Level_4c20_map[];
extern const char *Level_4c21_map[];

extern const char *Level_5c1_map[];
extern const char *Level_5c2_map[];
extern const char *Level_5c3_map[];
extern const char *Level_5c4_map[];
extern const char *Level_5c5_map[];
extern const char *Level_5c6_map[];
extern const char *Level_5c7_map[];
extern const char *Level_5c8_map[];
extern const char *Level_5c9_map[];
extern const char *Level_5c10_map[];
extern const char *Level_5c11_map[];
extern const char *Level_5c12_map[];
extern const char *Level_5c13_map[];
extern const char *Level_5c14_map[];
extern const char *Level_5c15_map[];
extern const char *Level_5c16_map[];
extern const char *Level_5c17_map[];
extern const char *Level_5c18_map[];
extern const char *Level_5c19_map[];
extern const char *Level_5c20_map[];
extern const char *Level_5c21_map[];
extern const char *Level_5c22_map[];

extern const char *Level_1b_map[];
extern const char *Level_2b_map[];
extern const char *Level_3b_map[];
extern const char *Level_4b_map[];
extern const char *Level_5b_map[];
extern const char *Level_6b_map[];



//==============================================//
//==> MODUL MANAGEMENT ARENA DAN LEVEL-LEVEL <==//
//==============================================//
/* {Sopian} */


#endif