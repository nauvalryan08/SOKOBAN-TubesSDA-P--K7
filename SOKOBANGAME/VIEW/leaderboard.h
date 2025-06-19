#ifndef LEADERBOARDSCREEN_H
#define LEADERBOARDSCREEN_H

#include "viewtoolkit.h"
#include "../UTILS/sound/soundmanager.h"
#include "../UTILS/include/curses.h"
#include "../GAMEPLAY/ARENA_LOGIC/Level.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define n_chapters 5

void show_leaderboard();
void ch1_leaderboard();
void ch2_leaderboard();
void ch3_leaderboard();
void ch4_leaderboard();
void ch5_leaderboard();

#endif