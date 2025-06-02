#ifndef LEVELSCREEN_H
#define LEVELSCREEN_H

#include <curses.h>
#include "../GAMEPLAY/ARENA_LOGIC/RoomFactory.h"
#include "../GAMEPLAY/ARENA_LOGIC/Level.h"

// Function to display the level selection screen
void show_level_selection_screen();

// Function to handle level selection using arrow keys
LevelData* select_level();

// Function to display and run the selected level
void run_level(LevelData* selected_level);

// Helper function to display level information
void display_level_info(LevelData* level);

// Helper function to handle level input
int handle_level_input();

#endif // LEVEL_SCREEN_H 