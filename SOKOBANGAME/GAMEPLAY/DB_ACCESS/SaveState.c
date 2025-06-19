#include "SaveState.h"

//=================================================//
//==                DATABASE ACCESS              ==//
//=================================================//
/* {Sopian} */

//==> Memnyimpan Hasil data usai bermain
void save_data_to_database ( Queue *q, const char *username, const char *levelID, const char *dataID, ScoreData scoreData) {

    FILE *fp = fopen(PLAY_DATA_PATH, "a");
    if (!fp) return;

    // Tulis metadata
    fprintf(fp, "%s|%s|%s|%d|%d|%d|%d|",
        username,
        levelID,
        dataID,
        scoreData.score,
        scoreData.time,
        scoreData.TotalMove,
        scoreData.TotalUndo
    );

    // Tulis langkah-langkah replay (UDRLZ)
    Node *curr = q->front;
    while (curr) {
        ReplayStep *step = (ReplayStep *) curr->data;
        fprintf(fp, "%c", step->move);
        curr = curr->next;
    }

    fprintf(fp, "\n");
    fclose(fp);
}


//==> menyimpan State permainan saat Exit [untuk kembali dilanjutkan saat bermain lagi]
void save_game_state (const char* username, const char* level_id, RoomLayout* room) {
    SaveState save;
    strncpy(save.username, username, sizeof(save.username));
    strncpy(save.level_id, level_id, sizeof(save.level_id));
    save.room = *room;

    // Buka file index lama untuk baca
    FILE *index_old = fopen(INDEX_DATA_STATE_PATH, "r");
    FILE *index_new = fopen(TEMP_INDEX_PATH, "w"); // file index baru
    if (!index_new) return;

    char key_to_remove[64];
    sprintf(key_to_remove, "%s-%s", username, level_id);

    // Salin semua index kecuali yang ingin dihapus
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

    // Buka data file dan tulis data baru
    FILE *data = fopen(DATA_STATE_PATH, "ab");
    if (!data) {
        fclose(index_new);
        return;
    }

    fseek(data, 0, SEEK_END);
    long offset = ftell(data);
    
    fwrite(&save, sizeof(SaveState), 1, data);
    fclose(data);

    // Tambahkan entri index baru
    fprintf(index_new, "%s;%ld\n", key_to_remove, offset);
    fclose(index_new);

    // Ganti file index lama dengan yang baru
    remove(INDEX_DATA_STATE_PATH);
    rename(TEMP_INDEX_PATH, INDEX_DATA_STATE_PATH);
}


//==> Load gameState (mengambil data RoomLayout untuk nanti dijadikan aacuan start game)
int load_game_state (const char* username, const char* level_id, RoomLayout* room) {
    FILE *index = fopen(INDEX_DATA_STATE_PATH, "r");    //read 
    FILE *data = fopen(DATA_STATE_PATH, "rb");     //read Binary
    if (!index || !data) return 0; //Gagal membuka file

    char line[100], key[40];
    sprintf(key, "%s-%s", username, level_id);
    long offset = -1;       //

    char fileKey[40];
    long fileOffset;

    while (fgets(line, sizeof(line), index)) {
        sscanf(line, "%[^;];%ld", fileKey, &fileOffset);    //mengambil data dengamn format
        if (strcmp(fileKey, key) == 0) {                // JIka sama key nya
            offset = fileOffset;
            break;
        }
    }

    fclose(index);  //index didapatkan
    if (offset == -1) { //data tidak dotermukan sama sekali
        fclose(data);
        return 0;       //tidak ditemukan
    }

    fseek(data, offset, SEEK_SET);
    SaveState loaded;
    fread(&loaded, sizeof(SaveState), 1, data);
    *room = loaded.room;
    fclose(data);
    return 1;

}

// ===> menghapus data state yang sudah dipakai

void remove_game_state_entry(const char* username, const char* level_id) {
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

    char key_to_remove[64];
    sprintf(key_to_remove, "%s-%s", username, level_id);

    char line[100], fileKey[64];
    long fileOffset;
    SaveState buffer;
    long new_offset = 0;

    while (fgets(line, sizeof(line), index_old)) {
        sscanf(line, "%[^;];%ld", fileKey, &fileOffset);

        // Pindah ke offset di data lama
        fseek(data_old, fileOffset, SEEK_SET);
        fread(&buffer, sizeof(SaveState), 1, data_old);

        // Jika bukan data yang ingin dihapus, tulis ulang ke file baru
        if (strcmp(fileKey, key_to_remove) != 0) {
            // tulis ke data baru
            fwrite(&buffer, sizeof(SaveState), 1, data_new);
            // tulis ke index baru dengan offset baru
            fprintf(index_new, "%s;%ld\n", fileKey, new_offset);
            new_offset += sizeof(SaveState);
        }
    }

    // Tutup semua
    fclose(index_old);
    fclose(data_old);
    fclose(index_new);
    fclose(data_new);

    // Replace file lama dengan yang baru
    remove(INDEX_DATA_STATE_PATH);
    remove(DATA_STATE_PATH);
    rename(TEMP_INDEX_PATH, INDEX_DATA_STATE_PATH);
    rename("temp_data.dat", DATA_STATE_PATH);
}