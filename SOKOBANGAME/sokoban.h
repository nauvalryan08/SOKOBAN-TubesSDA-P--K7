#ifndef SOKOBAN_H
#define SOKOBAN_H

// Standar C
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ncurses
#include "UTILS/include/curses.h"

// Boolean
#include "UTILS/include/boolean.h"

// Music
#include "UTILS/sound/soundmanager.h"

// Auth
#include "UTILS/auth/authentication.h"

// Semua header proyek
#include "DATABASE/DataHierarki.h"
#include "DATABASE/DatabasePath.h"
#include "DATABASE/Player.h"


#include "GAMEPLAY/ARENA_LOGIC/RoomFactory.h"
#include "GAMEPLAY/ARENA_LOGIC/level.h"
#include "GAMEPLAY/ARENA_LOGIC/ChapterManager.h"


#include "GAMEPLAY/GAME_LOGIC/ButtonGame.h"
#include "GAMEPLAY/GAME_LOGIC/GameLogic.h"
#include "GAMEPLAY/GAME_LOGIC/GameStart.h"
#include "GAMEPLAY/REPLAY_LOGIC/ReplayGame.h"

#include "VIEW/lobbyscreen.h"
#include "VIEW/LevelScreen.h"
#include "VIEW/chapterscreen.h"
#include "VIEW/tutorial.h"
#include "VIEW/lobbyaltscreen.h"


#endif
