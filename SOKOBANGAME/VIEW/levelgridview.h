#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include "viewtoolkit.h"
#include "../UTILS/sound/soundmanager.h"
#include "../UTILS/include/curses.h"
#include "../GAMEPLAY/ARENA_LOGIC/Level.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum {
    LEADERBOARD,
    HISTORY
} context;

typedef enum {
    CHAPTER_1 = 0,
    CHAPTER_2,
    CHAPTER_3,
    CHAPTER_4,
    CHAPTER_5
} chapter_index;

#define n_chapters 5

// Mendapatkan judul untuk chapter dan konteks tertentu (LEADERBOARD/HISTORY)
const char* get_chapter_title(chapter_index chapter, context option);
void ch1_grid(context option);
void ch2_grid(context option);
void ch3_grid(context option);
void ch4_grid(context option);
void ch5_grid(context option);

#endif