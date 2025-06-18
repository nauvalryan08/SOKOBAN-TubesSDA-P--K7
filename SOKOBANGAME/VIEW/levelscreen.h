#ifndef LEVELSCREEN_H
#define LEVELSCREEN_H
#define NCURSES_MOUSE_VERSION

#include "../UTILS/include/curses.h"
#include "../UTILS/sound/soundmanager.h"
#include "../GAMEPLAY/ARENA_LOGIC/RoomFactory.h"
#include "../GAMEPLAY/ARENA_LOGIC/Level.h"
#include "../GAMEPLAY/ARENA_LOGIC/ChapterManager.h"

#include "../GAMEPLAY/GAME_LOGIC/GameStart.h"
#include "../STRUCTURES/tree.h"
#include <string.h>

#define MAX_LEVELS_PER_COLUMN 20
#define MAX_COLUMNS 5

typedef struct{
    LevelData *array[100];
    int count;
}LevelCollector;

// Helper Function for display level
void store_level_data (void* data, LevelCollector *collector);
void store_callback_wrapper (void* data);

// Function to display the level selection screen
void show_level_selection_screen(LevelData* levels[], int count );

// Function to handle level selection using arrow keys
LevelData* select_level();

// Generic level selection function
LevelData* select_level_from_list(LevelData* levels[], int count);

// Function to display and run the selected level
void run_level(LevelData* selected_level, ChapterData* current_chapter, const char *username);

// Helper function to display level information
void display_level_info(LevelData* level);

LevelData* tutorial_screen();
LevelData* chapter1_screen();
LevelData* chapter2_screen();
LevelData* chapter3_screen();
LevelData* chapter4_screen();
LevelData* chapter5_screen();

#endif // LEVEL_SCREEN_H 