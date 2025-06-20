#ifndef PLAY_DATA_ACCESS_H
#define PLAY_DATA_ACCESS_H

#include "../GAMEPLAY/DB_ACCESS/SaveState.h"

// History Filtering
int compare_score_desc(const void *a, const void *b);
void load_data_filter_by_name(PlayData data[10], const char level_id[20], const char username[20]);
void load_data_filter_by_score(PlayData data[10], const char level_id[20]);

#endif // PLAY_DATA_ACCESS_H