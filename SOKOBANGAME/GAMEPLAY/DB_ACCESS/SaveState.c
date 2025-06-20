#include "SaveState.h"

//=================================================//
//==                DATABASE ACCESS              ==//
//=================================================//
/* {Sopian} */

//==> Memnyimpan Hasil data usai bermain
void save_data_to_database(const char* username, const char* ID_level, int ID_data, ScoreData scoreData, Queue *replayQueue) {
    FILE *fp = fopen(PLAY_DATA_PATH, "a");
    if (!fp) return;

    fprintf(fp, "%s|%s|%d|%d|%d|%d|%d|",
        username,
        ID_level,
        ID_data,
        scoreData.score,
        scoreData.time,
        scoreData.TotalMove,
        scoreData.TotalUndo
    );

    Node *curr = replayQueue->front;
    while (curr) {
        ReplayStep *step = (ReplayStep *) curr->data;
        fprintf(fp, "%c", step->move);
        curr = curr->next;
    }

    fprintf(fp, "\n");
    fclose(fp);
}



//==> load data play berdasarakn ID
Boolean load_play_data_by_id(const char* username, int ID_data, ScoreData* out, Queue* replay) {
    FILE* fp = fopen(PLAY_DATA_PATH, "r");
    if (!fp) return false;

    char line[2048];
    while (fgets(line, sizeof(line), fp)) {
        char uname[20], level_id[20];
        int data_id, score, time, move, undo;
        char replayStr[1024];

        sscanf(line, "%[^|]|%[^|]|%d|%d|%d|%d|%d|%s", uname, level_id, &data_id, &score, &time, &move, &undo, replayStr);

        if (strcmp(username, uname) == 0 && data_id == ID_data) {
            out->score = score;
            out->time = time;
            out->TotalMove = move;
            out->TotalUndo = undo;

            initQueue(replay);
            for (int i = 0; replayStr[i]; ++i) {
                enqueue(replay, createStep(replayStr[i]));
            }
            fclose(fp);
            return true;
        }
    }

    fclose(fp);
    return false;
}


//==> menyimpan State permainan saat Exit [untuk kembali dilanjutkan saat bermain lagi]
void save_game_state(const char* username, const char* ID_level, int ID_data, RoomLayout* room) {
    SaveState save;
    strncpy(save.username, username, sizeof(save.username));
    strncpy(save.ID_level, ID_level, sizeof(save.ID_level));
    save.ID_data = ID_data;
    save.room = *room;

    FILE *index_old = fopen(INDEX_DATA_STATE_PATH, "r");
    FILE *index_new = fopen(TEMP_INDEX_PATH, "w");
    if (!index_new) return;

    char key_to_remove[128];
    sprintf(key_to_remove, "%d-%s-%s", ID_data ,username, ID_level);

    if (index_old) {
        char line[100], fileKey[64];
        long offset;
        while (fgets(line, sizeof(line), index_old)) {
            sscanf(line, "%[^;];%ld", fileKey, &offset);
            if (strcmp(fileKey, key_to_remove) != 0) {
                fputs(line, index_new);
            }
        }
        fclose(index_old);
    }

    FILE *data = fopen(DATA_STATE_PATH, "ab");
    if (!data) {
        fclose(index_new);
        return;
    }

    fseek(data, 0, SEEK_END);
    long offset = ftell(data);
    fwrite(&save, sizeof(SaveState), 1, data);
    fclose(data);

    fprintf(index_new, "%s;%ld\n", key_to_remove, offset);
    fclose(index_new);

    remove(INDEX_DATA_STATE_PATH);
    rename(TEMP_INDEX_PATH, INDEX_DATA_STATE_PATH);
}


//==> Load gameState (mengambil data RoomLayout untuk nanti dijadikan aacuan start game)
int load_game_state(const char* username, const char* ID_level, SaveState* outSave) {
    FILE *index = fopen(INDEX_DATA_STATE_PATH, "r");
    FILE *data = fopen(DATA_STATE_PATH, "rb");
    if (!index || !data) return 0;

    char line[256], fileKey[128];
    long offset;
    while (fgets(line, sizeof(line), index)) {
        sscanf(line, "%[^;];%ld", fileKey, &offset);

        // Pecah key: idData-username-ID_level
        int id;
        char uname[64], levelid[64];
        sscanf(fileKey, "%d-%[^-]-%s", &id, uname, levelid);

        if (strcmp(uname, username) == 0 && strcmp(levelid, ID_level) == 0) {
            fseek(data, offset, SEEK_SET);
            fread(outSave, sizeof(SaveState), 1, data);
            fclose(index);
            fclose(data);
            return 1;
        }
    }

    fclose(index);
    fclose(data);
    return 0;
}




// ===> menghapus data state yang sudah dipakai
void remove_game_state_entry(const char* username, const char* ID_level, int ID_data) {
    FILE *index_old = fopen(INDEX_DATA_STATE_PATH, "r");
    FILE *data_old = fopen(DATA_STATE_PATH, "rb");
    FILE *index_new = fopen(TEMP_INDEX_PATH, "w");
    FILE *data_new = fopen("temp_data.dat", "wb");

    if (!index_old || !data_old || !index_new || !data_new) {
        if (index_old) fclose(index_old);
        if (data_old) fclose(data_old);
        if (index_new) fclose(index_new);
        if (data_new) fclose(data_new);
        return;
    }

    char key_to_remove[128];
    sprintf(key_to_remove, "%d-%s-%s", ID_data, username, ID_level);

    char line[256], fileKey[128];
    long fileOffset, new_offset = 0;
    SaveState buffer;

    while (fgets(line, sizeof(line), index_old)) {
        sscanf(line, "%[^;];%ld", fileKey, &fileOffset);
        fseek(data_old, fileOffset, SEEK_SET);
        fread(&buffer, sizeof(SaveState), 1, data_old);

        if (strcmp(fileKey, key_to_remove) != 0) {
            fwrite(&buffer, sizeof(SaveState), 1, data_new);
            fprintf(index_new, "%s;%ld\n", fileKey, new_offset);
            new_offset += sizeof(SaveState);
        }
    }

    fclose(index_old);
    fclose(data_old);
    fclose(index_new);
    fclose(data_new);

    remove(INDEX_DATA_STATE_PATH);
    remove(DATA_STATE_PATH);
    rename(TEMP_INDEX_PATH, INDEX_DATA_STATE_PATH);
    rename("temp_data.dat", DATA_STATE_PATH);
}




//====================//
// -. TEMP FILE .-    //
//====================//

void save_temp_play_data(const char* username, const char* ID_level, int ID_data, ScoreData scoreData, Queue* replayQueue) {
    // Buat key unik: ID_data-username-ID_level
    char key_to_save[128];
    sprintf(key_to_save, "%d-%s-%s", ID_data, username, ID_level);

    // Hapus entry lama dengan key yang sama
    FILE *fp_old = fopen(TEMP_PLAYDATA_PATH, "r");
    FILE *fp_new = fopen(TEMP_INDEX_PATH, "w");

    if (fp_old && fp_new) {
        char line[2048];
        while (fgets(line, sizeof(line), fp_old)) {
            int id;
            char uname[32], levelid[32];
            sscanf(line, "%d|%[^|]|%[^|]", &id, uname, levelid);

            char current_key[128];
            sprintf(current_key, "%d-%s-%s", id, uname, levelid);

            if (strcmp(current_key, key_to_save) != 0) {
                fputs(line, fp_new);
            }
        }
        fclose(fp_old);
        fclose(fp_new);

        remove(TEMP_PLAYDATA_PATH);
        rename(TEMP_INDEX_PATH, TEMP_PLAYDATA_PATH);
    } else {
        if (fp_old) fclose(fp_old);
        if (fp_new) fclose(fp_new);
    }

    // Sekarang append data baru
    FILE *fp = fopen(TEMP_PLAYDATA_PATH, "a");
    if (!fp) return;

    fprintf(fp, "%d|%s|%s|%d|%d|%d|%d|", ID_data, username, ID_level,
            scoreData.score, scoreData.time, scoreData.TotalMove, scoreData.TotalUndo);

    Node *curr = replayQueue->front;
    while (curr) {
        ReplayStep *step = (ReplayStep *)curr->data;
        fprintf(fp, "%c", step->move);
        curr = curr->next;
    }
    fprintf(fp, "\n");
    fclose(fp);
}

Boolean load_temp_play_data(const char* username, int ID_data, ScoreData* out, Queue* replay) {
    FILE *fp = fopen(TEMP_PLAYDATA_PATH, "r");
    if (!fp) return false;

    char line[2048];
    while (fgets(line, sizeof(line), fp)) {
        char uname[32], level_id[32], replayStr[1024];
        int data_id, score, time, move, undo;

        sscanf(line, "%d|%[^|]|%[^|]|%d|%d|%d|%d|%s",
               &data_id, uname, level_id, &score, &time, &move, &undo, replayStr);

        if (strcmp(uname, username) == 0 && data_id == ID_data) {
            out->score = score;
            out->time = time;
            out->TotalMove = move;
            out->TotalUndo = undo;

            initQueue(replay);
            for (int i = 0; replayStr[i]; ++i) {
                enqueue(replay, createStep(replayStr[i]));
            }
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}


void remove_temp_play_data_entry(const char* username, int ID_data, const char* ID_level) {
    FILE *fp_old = fopen(TEMP_PLAYDATA_PATH, "r");
    FILE *fp_new = fopen(TEMP_INDEX_PATH, "w");
    if (!fp_old || !fp_new) {
        if (fp_old) fclose(fp_old);
        if (fp_new) fclose(fp_new);
        return;
    }

    char line[2048];
    while (fgets(line, sizeof(line), fp_old)) {
        int data_id;
        char uname[32], levelid[32];
        sscanf(line, "%d|%[^|]|%[^|]", &data_id, uname, levelid);

        if (!(data_id == ID_data && strcmp(uname, username) == 0 && strcmp(levelid, ID_level) == 0)) {
            fputs(line, fp_new);
        }
    }

    fclose(fp_old);
    fclose(fp_new);
    remove(TEMP_PLAYDATA_PATH);
    rename(TEMP_INDEX_PATH, TEMP_PLAYDATA_PATH);
}



// ======================== //
// > History & leaderBoard //
//========================//


int load_all_play_data_by_level(const char* id_level, PlayData** outData) {
    FILE* file = fopen(PLAY_DATA_PATH, "r");
    if (!file) return 0;

    int capacity = 10, count = 0;
    *outData = malloc(capacity * sizeof(PlayData));
    PlayData temp;
    while (fread(&temp, sizeof(PlayData), 1, file)) {
        if (strcmp(temp.ID_level, id_level) == 0) {
            if (count >= capacity) {
                capacity *= 2;
                *outData = realloc(*outData, capacity * sizeof(PlayData));
            }
            (*outData)[count++] = temp;
        }
    }
    fclose(file);
    return count;
}
