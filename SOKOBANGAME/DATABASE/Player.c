#include "player.h"

PlayerData players[MAX_PLAYERS];
int player_count = 0;

// Fungsi untuk mengonversi string level_id menjadi enum LevelID
LevelID level_id_from_string(const char *level_id_str) {
    for (LevelID i = 0; i < LEVEL_COUNT; i++) {
        if (strcmp(ALL_LEVELS[i].level_id, level_id_str) == 0) {
            return i;
        }
    }
    return LEVEL_COUNT; // Return invalid jika tidak ditemukan
}

// Fungsi untuk mengonversi enum LevelID menjadi string
const char* level_id_to_string(LevelID level_id) {
    if (level_id < LEVEL_COUNT) {
        return ALL_LEVELS[level_id].level_id;
    }
    return "INVALID_LEVEL";
}

// Fungsi untuk mendapatkan chapter berdasarkan level
ChapterTree get_chapter_for_level(LevelID level_id) {
    if (level_id >= LEVEL_1T1 && level_id <= LEVEL_1T4) return TUTORIAL;
    if (level_id >= LEVEL_1C1 && level_id <= LEVEL_1C8) return CHAPTER1;
    if (level_id >= LEVEL_2C1 && level_id <= LEVEL_2C15) return CHAPTER2;
    if (level_id >= LEVEL_3C1 && level_id <= LEVEL_3C18) return CHAPTER3;
    if (level_id >= LEVEL_4C1 && level_id <= LEVEL_4C21) return CHAPTER4;
    if (level_id >= LEVEL_5C1 && level_id <= LEVEL_5C22) return CHAPTER5;

    // Bonus Level
    if (level_id = LEVEL_1B) return CHAPTER2;
    if (level_id = LEVEL_2B) return CHAPTER3;
    if (level_id = LEVEL_3B) return CHAPTER4;
    if (level_id = LEVEL_5B) return CHAPTER5;
    if (level_id = LEVEL_6B) return CHAPTER5;

    return TUTORIAL; // Default
}


// Function untuk mengembalikan Player username yang tersimpan
PlayerData* get_player(const char *username) {
    for (int i = 0; i < player_count; i++) {
        if (strcmp(players[i].username, username) == 0) {
            return &players[i];
        }
    }
    return NULL;
}

// Function untuk membuat data Player baru
void create_player(const char *username) {
    if (player_count >= MAX_PLAYERS || get_player(username) != NULL) {
        return;
    }
    
    PlayerData new_player;
    strncpy(new_player.username, username, MAX_USERNAME_LEN);
    new_player.id = player_count + 1;
    new_player.current_chapter = TUTORIAL;
    new_player.current_level = LEVEL_1T1;
    
    players[player_count++] = new_player;
    save_all_players();
}

// Function untuk mengupdate progress Player di game
void update_player_progress(const char *username, ChapterTree chapter, LevelID level) {
    PlayerData* player = get_player(username);
    if (player != NULL) {
        player->current_chapter = chapter;
        player->current_level = level;
        save_all_players();
    }
}


// Function untuk menyimpan seluruh data Player
void save_all_players() {
    FILE* file = fopen(PLAYER_DB_FILE, "wb");
    if (file) {
        fwrite(&player_count, sizeof(int), 1, file);
        fwrite(players, sizeof(PlayerData), player_count, file);
        fclose(file);
    }
}

// Fungsi untuk memuat semua Player
void load_all_players() {
    FILE* file = fopen(PLAYER_DB_FILE, "rb");
    if (file) {
        fread(&player_count, sizeof(int), 1, file);
        fread(players, sizeof(PlayerData), player_count, file);
        fclose(file);
    }
}

// ---------------------------------------------------------- //
//     Function untuk mendapat Chapter dan Level terakhir     //
// ---------------------------------------------------------- //

ChapterTree get_player_chapter(const char *username) {
    PlayerData* player = get_player(username);
    return player ? player->current_chapter : TUTORIAL;
}

LevelID get_player_level(const char *username) {
    PlayerData* player = get_player(username);
    return player ? player->current_level : LEVEL_1T1;
}

void unlock_levels_based_on_progress(const char *username) {
    PlayerData* player = get_player(username);
    if (!player) return;

    // Reset semua level menjadi terkunci
    for (int i = 0; i < LEVEL_COUNT; i++) {
        ALL_LEVELS[i].is_unlocked = false;
    }

    // Unlock semua level sampai progress terakhir
    for (LevelID i = 0; i <= player->current_level; i++) {
        // Hanya unlock jika chapter level <= chapter progress pemain
        if (get_chapter_for_level(i) <= player->current_chapter) {
            ALL_LEVELS[i].is_unlocked = true;
        }
    }

    // Unlock semua level di chapter yang lebih rendah
    for (int i = 0; i < player->current_chapter; i++) {
        for (int j = 0; j < LEVEL_COUNT; j++) {
            if (get_chapter_for_level(j) == i) {
                ALL_LEVELS[j].is_unlocked = true;
            }
        }
    }
}