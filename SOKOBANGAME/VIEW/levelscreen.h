#ifndef LEVELSCREEN_H
#define LEVELSCREEN_H

#include "../UTILS/include/curses.h"
#include "../UTILS/sound/soundmanager.h"
#include "../GAMEPLAY/ARENA_LOGIC/RoomFactory.h"
#include "../GAMEPLAY/ARENA_LOGIC/Level.h"
#include "../GAMEPLAY/ARENA_LOGIC/ChapterManager.h"

#include "../GAMEPLAY/GAME_LOGIC/GameStart.h"
#include "../STRUCTURES/tree.h"

// Function to display the level selection screen
void show_level_selection_screen(LevelData* levels[], int count );

// Function to handle level selection using arrow keys
LevelData* select_level();

// Generic level selection function
LevelData* select_level_from_list(LevelData* levels[], int count);

// Tutorial levels selection
LevelData* select_level_tutorial();

LevelData* select_level_chapter1();

LevelData* select_level_chapter2() ;

LevelData* select_level_chapter3();

LevelData* select_level_chapter4();

LevelData* select_level_chapter5();


// Function to display and run the selected level
void run_level(LevelData* selected_level, ChapterData* current_chapter, const char *username);

// Helper function to display level information
void display_level_info(LevelData* level);

#endif // LEVEL_SCREEN_H 