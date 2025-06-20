#ifndef PLAYER_H
#define PLAYER_H

#include "../GAMEPLAY/ARENA_LOGIC/ChapterManager.h"
#include "../GAMEPLAY/ARENA_LOGIC/Level.h"
#include "../GAMEPLAY/GAME_LOGIC/GameLogic.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PLAYERS 100
#define PLAYER_DB_FILE "./SOKOBANGAME/DATABASE/players.dat"
#define MAX_USERNAME_LEN 20
#define MAX_FINISHED_PER_CHAPTER 25


typedef struct {
    char username[20];
    int id;                                 
    ChapterTree current_chapter;        //chapter saat ini
    LevelID finished[LEVEL_COUNT];      //Data level yang finished di current chapter/
    int finished_count;                 //Jumlah level yang disimpan
} PlayerData;

extern PlayerData players[MAX_PLAYERS]; // Deklarasikan sebagai extern
extern int player_count; // Deklarasikan sebagai extern

// Fungsi manajemen data pemain
PlayerData* get_player(const char *username);
void create_player(const char *username);
void update_player_progress(const char *username, LevelID level);
void save_all_players();
void load_all_players();

// Fungsi progress
ChapterTree get_player_chapter(const char *username);
void unlock_levels_based_on_progress(const char *username);

// Fungsi utilitas
LevelID level_id_from_string(const char *level_id_str);
const char* level_id_to_string(LevelID level_id);
ChapterTree get_chapter_for_level(LevelID level_id);

#endif