#ifndef LEVEL_H
#define LEVEL_H

#include "RoomFactory.h"

//==> STRUCT LEVEL DATA, [UNTUK TREE CHAPTER NANTI]
typedef struct {
    const char *level_id;           //Untuk traversal dan searching
    const char *level_name;         //Display name saat runtime
    const char **map;               //Map level
    boolean is_unlcoked;            //Status unlocked
    boolean is_finished;            //Status pernah diselesaikan
}LevelData;


//==> TYPEDEF INDEKS LEVEL MENGGUNAKAN NAMA LEVEL
typedef enum {
    LEVEL_1C1,
    LEVEL_1C2,
    LEVEL_1C3,
    LEVEL_1C4,
    LEVEL_1C5,
    LEVEL_1C6,
    LEVEL_1C7,
    LEVEL_1C8,
    LEVEL_1C9,
    LEVEL_1C10,
    LEVEL_1C11,
    LEVEL_1C12,
    LEVEL_1C13,
    LEVEL_1C14,
    LEVEL_1C15,
    LEVEL_1C16,
    LEVEL_1C17,
    LEVEL_1C18,
    LEVEL_1C19,
    LEVEL_1C20,
    LEVEL_1C21,
    LEVEL_1C22,
    LEVEL_1C23,
    LEVEL_1C24,
    LEVEL_1C25,
    LEVEL_1C26,
    LEVEL_1C27,
    LEVEL_1C28,
    LEVEL_1C29,
    LEVEL_1C30,
    LEVEL_1C31,
    LEVEL_1C32,
    LEVEL_1C33,
    LEVEL_1C34,
    LEVEL_1C35,
    LEVEL_1C36,
    LEVEL_1C37,
    LEVEL_1C38,
    LEVEL_1C39,
    LEVEL_1C40,
    LEVEL_1C41,
    LEVEL_1C42,
    LEVEL_1C43,
    LEVEL_1C44,
    LEVEL_1C45,
    LEVEL_1C46,
    LEVEL_1C47,
    LEVEL_1C48,
    LEVEL_1C49,
    LEVEL_1C50,
    LEVEL_1C51,
    LEVEL_1C52,
    LEVEL_1C53,
    LEVEL_1C54,
    LEVEL_1C55,
    LEVEL_1C56,
    LEVEL_1C57,
    LEVEL_1C58,
    LEVEL_1C59,
    LEVEL_1C60,
    LEVEL_1C61,
    LEVEL_1C62,
    LEVEL_1C63,
    LEVEL_1C64,
    LEVEL_1C65,
    LEVEL_1C66,
    LEVEL_1C67,
    LEVEL_1C68,
    LEVEL_1C69,
    LEVEL_1C70,
    LEVEL_1C71,
    LEVEL_1C72,
    LEVEL_1C73,
    LEVEL_1C74,
    LEVEL_1C75,
    LEVEL_1C76,
    LEVEL_1C77,
    LEVEL_1C78,
    LEVEL_1C79,
    LEVEL_1C80,
    LEVEL_1C81,
    LEVEL_1C82,
    LEVEL_1C83,
    LEVEL_1C84,
    LEVEL_1C85,
    LEVEL_1C86,
    LEVEL_1C87,
    LEVEL_1C88,
    LEVEL_1C89,
    LEVEL_1C90,
    LEVEL_1C91,
    LEVEL_1C92,
    LEVEL_1C93,
    LEVEL_1C94,
    LEVEL_COUNT
} LevelID;


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
extern const char *Level_1c9_map[];
extern const char *Level_1c10_map[];
extern const char *Level_1c11_map[];
extern const char *Level_1c12_map[];
extern const char *Level_1c13_map[];
extern const char *Level_1c14_map[];
extern const char *Level_1c15_map[];
extern const char *Level_1c16_map[];
extern const char *Level_1c17_map[];
extern const char *Level_1c18_map[];
extern const char *Level_1c19_map[];
extern const char *Level_1c20_map[];
extern const char *Level_1c21_map[];
extern const char *Level_1c22_map[];
extern const char *Level_1c23_map[];
extern const char *Level_1c24_map[];
extern const char *Level_1c25_map[];
extern const char *Level_1c26_map[];
extern const char *Level_1c27_map[];
extern const char *Level_1c28_map[];
extern const char *Level_1c29_map[];
extern const char *Level_1c30_map[];
extern const char *Level_1c31_map[];
extern const char *Level_1c32_map[];
extern const char *Level_1c33_map[];
extern const char *Level_1c34_map[];
extern const char *Level_1c35_map[];
extern const char *Level_1c36_map[];
extern const char *Level_1c37_map[];
extern const char *Level_1c38_map[];
extern const char *Level_1c39_map[];
extern const char *Level_1c40_map[];
extern const char *Level_1c41_map[];
extern const char *Level_1c42_map[];
extern const char *Level_1c43_map[];
extern const char *Level_1c44_map[];
extern const char *Level_1c45_map[];
extern const char *Level_1c46_map[];
extern const char *Level_1c47_map[];
extern const char *Level_1c48_map[];
extern const char *Level_1c49_map[];
extern const char *Level_1c50_map[];
extern const char *Level_1c51_map[];
extern const char *Level_1c52_map[];
extern const char *Level_1c53_map[];
extern const char *Level_1c54_map[];
extern const char *Level_1c55_map[];
extern const char *Level_1c56_map[];
extern const char *Level_1c57_map[];
extern const char *Level_1c58_map[];
extern const char *Level_1c59_map[];
extern const char *Level_1c60_map[];
extern const char *Level_1c61_map[];
extern const char *Level_1c62_map[];
extern const char *Level_1c63_map[];
extern const char *Level_1c64_map[];
extern const char *Level_1c65_map[];
extern const char *Level_1c66_map[];
extern const char *Level_1c67_map[];
extern const char *Level_1c68_map[];
extern const char *Level_1c69_map[];
extern const char *Level_1c70_map[];
extern const char *Level_1c71_map[];
extern const char *Level_1c72_map[];
extern const char *Level_1c73_map[];
extern const char *Level_1c74_map[];
extern const char *Level_1c75_map[];
extern const char *Level_1c76_map[];
extern const char *Level_1c77_map[];
extern const char *Level_1c78_map[];
extern const char *Level_1c79_map[];
extern const char *Level_1c80_map[];
extern const char *Level_1c81_map[];
extern const char *Level_1c82_map[];
extern const char *Level_1c83_map[];
extern const char *Level_1c84_map[];
extern const char *Level_1c85_map[];
extern const char *Level_1c86_map[];
extern const char *Level_1c87_map[];
extern const char *Level_1c88_map[];
extern const char *Level_1c89_map[];
extern const char *Level_1c90_map[];
extern const char *Level_1c91_map[];
extern const char *Level_1c92_map[];
extern const char *Level_1c93_map[];
extern const char *Level_1c94_map[];



//==============================================//
//==> MODUL MANAGEMENT ARENA DAN LEVEL-LEVEL <==//
//==============================================//
/* {Sopian} */

LevelData* get_level_by_id(const char* level_id);


#endif