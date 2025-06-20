#ifndef PLAY_DATA_MANAGER_H
#define PLAY_DATA_MANAGER_H

#include "../GAMEPLAY/DB_ACCESS/SaveState.h"
#include "DatabasePath.h"


typedef struct {
    char username[20];
    char ID_level[20];
    int score;
    long offset;
} PlayDataIndexMinimal;

// Load dan Sorting berdasarakn Username

int load_play_data_by_username(const char* username, PlayData** outData);

//Load dan Sorting berdasarakan score
int load_play_data_sorted_by_score(PlayData** outData);

// Membuat file yang sudah tersortir berdasarakn score
void save_sorted_play_data_by_score();

// Membbuat file yang sudah tersortir berdasarakan username
void save_sorted_play_data_by_name();


// === > Load data form sorted file
int load_all_playdata_from_sorted_score(PlayDataIndexMinimal** outData);
int load_all_playdata_from_sorted_name(PlayDataIndexMinimal** outData);



//==> Helper :
int compare_name(const void* a, const void* b);

int compare_level_then_score_desc(const void* a, const void* b);

#endif