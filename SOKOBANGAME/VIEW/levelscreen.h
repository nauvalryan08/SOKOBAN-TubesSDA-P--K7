#ifndef LEVELSCREEN_H
#define LEVELSCREEN_H
#define NCURSES_MOUSE_VERSION

#include "../UTILS/include/curses.h"
#include "../UTILS/sound/soundmanager.h"
#include "../DATABASE/Player.h"

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

// Fungsi bantu untuk menampilkan level
void store_level_data (void* data, LevelCollector *collector);
void store_callback_wrapper (void* data);

// Fungsi untuk menampilkan layar pemilihan level
void show_level_selection_screen(LevelData* levels[], int count );

// Fungsi untuk menangani pemilihan level menggunakan tombol panah
LevelData* select_level();

// Fungsi pemilihan level generik
LevelData* select_level_from_list(LevelData* levels[], int count);

// Fungsi untuk menampilkan dan menjalankan level yang dipilih
void run_level(LevelData* selected_level, ChapterData* current_chapter, const char *username);

// Fungsi bantu untuk menampilkan informasi level
void display_level_info(LevelData* level);

LevelData* tutorial_screen();
LevelData* chapter1_screen();
LevelData* chapter2_screen();
LevelData* chapter3_screen();
LevelData* chapter4_screen();
LevelData* chapter5_screen();

#endif // LEVEL_SCREEN_H 