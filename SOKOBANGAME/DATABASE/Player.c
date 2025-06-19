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
    if (player_count >= MAX_PLAYERS || get_player(username) != NULL) return;

    PlayerData new_player;
    strncpy(new_player.username, username, MAX_USERNAME_LEN);
    new_player.id = player_count + 1;
    new_player.current_chapter = TUTORIAL;
    new_player.finished_count = 0;

    players[player_count++] = new_player;
    save_all_players();
}

// Function untuk mengupdate progress Player di game
void update_player_progress(const char *username, LevelID level) {
    PlayerData* player = get_player(username);
    if (!player) return;

    ChapterTree chapter = get_chapter_for_level(level);
    if (chapter > player->current_chapter) {
        player->current_chapter = chapter;
    }

    for (int i = 0; i < player->finished_count; i++) {
        if (player->finished[i] == level) return;
    }
    if (player->finished_count < MAX_FINISHED_PER_CHAPTER) {
        player->finished[player->finished_count++] = level;
    }

    save_all_players();
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


// ------------------------------------------------------------ //
//     Function Unlocking level dan chapter sesaui progress     //
// ------------------------------------------------------------ //

// Helper: Tandai semua level di chapter sebagai finished dan unlocked
void mark_all_levels_finished_and_unlocked(void* data) {
    LevelData* lvl = (LevelData*)data;
    lvl->is_unlocked = true;
    lvl->is_finished = true;
}

// Helper: Tandai level sebagai finished jika ada dalam daftar player->finished[]
PlayerData* current_player_temp = NULL; // digunakan sebagai referensi global sementara

void mark_finished_levels_in_current_chapter(void* data) {
    LevelData* lvl = (LevelData*)data;
    for (int i = 0; i < current_player_temp->finished_count; i++) {
        if (current_player_temp->finished[i] == level_id_from_string(lvl->level_id)) {
            lvl->is_finished = true;
            lvl->is_unlocked = true;
            break;
        }
    }
}

void unlock_levels_based_on_progress(const char *username) {
    PlayerData* player = get_player(username);
    if (!player) return;

    // Reset semua level
    for (int i = 0; i < LEVEL_COUNT; i++) {
        ALL_LEVELS[i].is_unlocked = false;
        ALL_LEVELS[i].is_finished = false;
    }

    // Tandai semua level di chapter yang sudah dilewati sebagai selesai
    for (int i = 0; i < player->current_chapter; i++) {
        Ptree root = ChapterTrees[i].ChapterTree;
        preOrderTraversal(root, mark_all_levels_finished_and_unlocked);
    }

    // Tandai level-level yang diselesaikan di current chapter
    current_player_temp = player;
    for (int i = 0; i < player->finished_count; i++) {
        LevelID lid = player->finished[i];
        ALL_LEVELS[lid].is_finished = true;
        ALL_LEVELS[lid].is_unlocked = true;
    }

    // Update tree current chapter
    Ptree current_root = ChapterTrees[player->current_chapter].ChapterTree;
    preOrderTraversal(current_root, mark_finished_levels_in_current_chapter);
    unlock_child_if_parent_finished(current_root);

    ALL_LEVELS[LEVEL_1T1].is_unlocked = true;
    ALL_LEVELS[LEVEL_1T2].is_unlocked = true;
    ALL_LEVELS[LEVEL_1T3].is_unlocked = true;
    ALL_LEVELS[LEVEL_1T4].is_unlocked = true;
    ALL_LEVELS[LEVEL_1C1].is_unlocked = true;

    current_player_temp = NULL; // Bersihkan pointer global
}
