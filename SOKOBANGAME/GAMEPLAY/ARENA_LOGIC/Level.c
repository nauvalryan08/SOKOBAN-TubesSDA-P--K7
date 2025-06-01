#include "Level.h"

//====================//
//== PEMBUATAN AREA ==//
//====================//
/* {Sopian} */

const char *Level_1c1_map[] = {
    "####################",
    "#     @     $   .  #",
    "#                  #",
    "# .  $      F      #",
    "####################",
    NULL
};

const char *Level_1c2_map[] = {
    "####################",
    "# F            # . #",
    "#   $   #   $  #   #",
    "#       #   @      #",
    "#                  #",
    "#######    #########",
    "      # .  #        ",
    "      ######        ",   
    NULL
};

const char *Level_1c3_map[] = {
    "#################",
    "#F#     .       #",
    "# #   #     $   #",
    "# #   ######## #####",
    "#@  $ #            #",
    "##### # ############",
    "#.    $   .#        ",
    "############        ",   
    NULL
};

const char *Level_1c4_map[] = {
    "###################",
    "#       #####   #.#",
    "# ### #       # # #",
    "#   # $ # ### # #@#",
    "#   $ # #         #",
    "# # ### #$####### #",
    "#F#.#.            #",
    "###################",   
    NULL
};

const char *Level_1c5_map[] = {NULL};

const char *Level_1c6_map[] = {NULL};

const char *Level_1c7_map[] = {NULL};

const char *Level_1c8_map[] = {NULL};


//==============================================//
//==   PARSING ROOMLAYOUT MAP KE DALAM ARRAY  ==//
//==============================================//
/* {Sopian} */



//==============================================//
//==   DEFINISI SELURUH LEVEL KE DALAM ARRAY  ==//
//==============================================//
/* {Sopian} */

LevelData ALL_LEVELS[LEVEL_COUNT] = {
    [LEVEL_1C1] = {
        .level_id = "1c1",
        .level_name = "LEVEL 1",
        .map = Level_1c1_map,
        .is_unlcoked = true,
        .is_finished = false,
    },
    [LEVEL_1C2] = {
        .level_id = "1c2",
        .level_name = "LEVEL 2",
        .map = Level_1c2_map,
        .is_unlcoked = false,
        .is_finished = false,
    },
    [LEVEL_1C3] = {
        .level_id = "1c3",
        .level_name = "LEVEL 3",
        .map = Level_1c3_map,
        .is_unlcoked = false,
        .is_finished = false,
    },
    [LEVEL_1C4] = {
        .level_id = "1c4",
        .level_name = "LEVEL 4",
        .map = Level_1c4_map,
        .is_unlcoked = false,
        .is_finished = false,
    },
    [LEVEL_1C5] = {
        .level_id = "1c5",
        .level_name = "LEVEL 5",
        .map = Level_1c5_map,
        .is_unlcoked = false,
        .is_finished = false,
    },
    [LEVEL_1C6] = {
        .level_id = "1c6",
        .level_name = "LEVEL 6",
        .map = Level_1c6_map,
        .is_unlcoked = false,
        .is_finished = false,
    },
    [LEVEL_1C7] = {
        .level_id = "1c7",
        .level_name = "LEVEL 7",
        .map = Level_1c7_map,
        .is_unlcoked = false,
        .is_finished = false,
    },
    [LEVEL_1C8] = {
        .level_id = "1c8",
        .level_name = "LEVEL 8",
        .map = Level_1c6_map,
        .is_unlcoked = false,
        .is_finished = false,
    },
};
