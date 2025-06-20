// ========================
// PlayDataManager.c
// ========================
#include "PlayDataManager.h"
#include <stdlib.h>
#include <string.h>

//========//
// HELPER //
//=======//

int compare_level_then_score_desc(const void* a, const void* b) {
    PlayDataIndexMinimal* pa = (PlayDataIndexMinimal*)a;
    PlayDataIndexMinimal* pb = (PlayDataIndexMinimal*)b;
    int lvl_cmp = strcmp(pa->ID_level, pb->ID_level);
    if (lvl_cmp != 0) return lvl_cmp;
    return pb->score - pa->score;
}

int compare_name(const void* a, const void* b) {
    PlayDataIndexMinimal* pa = (PlayDataIndexMinimal*)a;
    PlayDataIndexMinimal* pb = (PlayDataIndexMinimal*)b;
    return strcmp(pa->username, pb->username);
}


// =================== //
// LOAD DATA LANGSUNG //
//====================//



// ================================= //
//          FILE SORTED SAVE         //
// ================================= //

void save_sorted_play_data_by_score() {
    FILE* file = fopen(PLAY_DATA_PATH, "r");
    if (!file) return;

    PlayDataIndexMinimal* list = malloc(1000 * sizeof(PlayDataIndexMinimal));
    char line[512];
    int count = 0;

    while (!feof(file)) {
        long offset = ftell(file);
        if (!fgets(line, sizeof(line), file)) break;
        if (strlen(line) < 5) continue;

        sscanf(line, "%19[^|]|%19[^|]|%*d|%d|%*d|%*d|%*d|%*s",
               list[count].username, list[count].ID_level, &list[count].score);
        list[count].offset = offset;
        count++;
    }
    fclose(file);

    qsort(list, count, sizeof(PlayDataIndexMinimal), compare_level_then_score_desc);

    FILE* out = fopen(PLAY_DATA_BY_SCORE_PATH, "wb");
    fwrite(list, sizeof(PlayDataIndexMinimal), count, out);
    fclose(out);
    free(list);
}

void save_sorted_play_data_by_name() {
    FILE* file = fopen(PLAY_DATA_PATH, "r");
    if (!file) return;

    PlayDataIndexMinimal* list = malloc(1000 * sizeof(PlayDataIndexMinimal));
    char line[512];
    int count = 0;

    while (!feof(file)) {
        long offset = ftell(file);
        if (!fgets(line, sizeof(line), file)) break;
        if (strlen(line) < 5) continue;

        sscanf(line, "%19[^|]|%19[^|]|%*d|%d|%*d|%*d|%*d|%*s",
               list[count].username, list[count].ID_level, &list[count].score);
        list[count].offset = offset;
        count++;
    }
    fclose(file);

    qsort(list, count, sizeof(PlayDataIndexMinimal), compare_name);

    FILE* out = fopen(PLAY_DATA_BY_NAME_PATH, "wb");
    fwrite(list, sizeof(PlayDataIndexMinimal), count, out);
    fclose(out);
    free(list);
}


// ================================= //
//          LOAD SORTED SAVE         //
// ================================= //

int load_all_playdata_from_sorted_score(PlayDataIndexMinimal** outData) {
    FILE* file = fopen(PLAY_DATA_BY_SCORE_PATH, "rb");
    if (!file) return 0;

    int capacity = 20, count = 0;
    *outData = malloc(capacity * sizeof(PlayDataIndexMinimal));
    PlayDataIndexMinimal temp;

    while (fread(&temp, sizeof(PlayDataIndexMinimal), 1, file)) {
        if (count >= capacity) {
            capacity *= 2;
            *outData = realloc(*outData, capacity * sizeof(PlayDataIndexMinimal));
        }
        (*outData)[count++] = temp;
    }

    fclose(file);
    return count;
}

int load_all_playdata_from_sorted_name(PlayDataIndexMinimal** outData) {
    FILE* file = fopen(PLAY_DATA_BY_NAME_PATH, "rb");
    if (!file) return 0;

    int capacity = 20, count = 0;
    *outData = malloc(capacity * sizeof(PlayDataIndexMinimal));
    PlayDataIndexMinimal temp;

    while (fread(&temp, sizeof(PlayDataIndexMinimal), 1, file)) {
        if (count >= capacity) {
            capacity *= 2;
            *outData = realloc(*outData, capacity * sizeof(PlayDataIndexMinimal));
        }
        (*outData)[count++] = temp;
    }

    fclose(file);
    return count;
}
