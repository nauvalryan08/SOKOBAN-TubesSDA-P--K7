#include "PlayDataAccess.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void load_data_filter_by_name(DoublyLinkedList *list, const char level_id[20], const char username[20]) {
    FILE *fp = fopen(PLAY_DATA_PATH, "r");
    if (!fp) return;

    char lines[1000][1024];
    int total_lines = 0;

    // Baca semua baris dulu
    while (fgets(lines[total_lines], sizeof(lines[0]), fp) && total_lines < 1000) {
        total_lines++;
    }
    fclose(fp);

    int count = 0;
    // Proses dari akhir ke awal
    for (int i = total_lines - 1; i >= 0 && count < 10; i--) {
        char uname[20], lvl_id[20], replayStr[1024];
        int data_id, score, time, move, undo;

        sscanf(lines[i], "%[^|]|%[^|]|%d|%d|%d|%d|%d|%s", uname, lvl_id, &data_id, &score, &time, &move, &undo, replayStr);

        if (strcmp(lvl_id, level_id) == 0 && strcmp(uname, username) == 0) {
            PlayData *pdata = (PlayData*)malloc(sizeof(PlayData));
            strcpy(pdata->username, uname);
            strcpy(pdata->ID_level, lvl_id);
            pdata->ID_data = data_id;
            pdata->scoreData.score = score;
            pdata->scoreData.time = time;
            pdata->scoreData.TotalMove = move;
            pdata->scoreData.TotalUndo = undo;
            pdata->replay_data = NULL;
            insertLast(list, pdata);
            count++;
        }
    }
}

int compare_score_desc(const void *a, const void *b) {
    PlayData *d1 = *(PlayData **)a;
    PlayData *d2 = *(PlayData **)b;
    return d2->scoreData.score - d1->scoreData.score;
}

void load_data_filter_by_score(DoublyLinkedList *list, const char level_id[20]) {
    FILE *fp = fopen(PLAY_DATA_PATH, "r");
    if (!fp) return;

    PlayData *allData[1000];
    int count = 0;

    char line[1024];
    while (fgets(line, sizeof(line), fp) && count < 1000) {
        char uname[20], lvl_id[20], replayStr[1024];
        int data_id, score, time, move, undo;

        sscanf(line, "%[^|]|%[^|]|%d|%d|%d|%d|%d|%s", uname, lvl_id, &data_id, &score, &time, &move, &undo, replayStr);

        if (strcmp(lvl_id, level_id) == 0) {
            PlayData *pdata = (PlayData*)malloc(sizeof(PlayData));
            strcpy(pdata->username, uname);
            strcpy(pdata->ID_level, lvl_id);
            pdata->ID_data = data_id;
            pdata->scoreData.score = score;
            pdata->scoreData.time = time;
            pdata->scoreData.TotalMove = move;
            pdata->scoreData.TotalUndo = undo;
            pdata->replay_data = NULL;
            allData[count] = pdata;
            count++;
        }
    }
    fclose(fp);

    // Urutkan dari skor tertinggi ke terendah
    qsort(allData, count, sizeof(PlayData*), compare_score_desc);

    int max = count < 10 ? count : 10;
    for (int i = 0; i < max; i++) {
        insertLast(list, allData[i]);
    }
    // Free unused PlayData
    for (int i = max; i < count; i++) {
        free(allData[i]);
    }
}
