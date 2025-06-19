#ifndef LEADERBOARDSCREEN_H
#define LEADERBOARDSCREEN_H

#include "viewtoolkit.h"
#include "levelgridview.h"
#include "../UTILS/sound/soundmanager.h"
#include "../UTILS/include/curses.h"
#include "../GAMEPLAY/ARENA_LOGIC/Level.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define n_chapters 5

void show_leaderboard();

#endif