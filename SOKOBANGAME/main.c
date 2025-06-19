#include "sokoban.h"

int main() {

    setlocale(LC_ALL, "");
    initscr();

    threadPlayBGMusic();       // Mulai BGM
    setBGMVolume(25); 
    
    // Inisialisasi warna
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(9, COLOR_BLACK, COLOR_WHITE);

    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    int menu_choice;
    RoomLayout room;
    LevelData *selected_level;
    Ptree PlayData = initDataHierarki();
    pthread_t enterSound;

    initAllChapters();
    load_all_players(); // Memuat data player saat program dimulai
    const char* current_username;
    // const char* dummyUsername = "Argiansah";

    while (menu_choice != 5) {
    // Handle pilihan menu

        menu_choice = show_alt_lobby();
        
        switch (menu_choice) {
        case 1: // Play Game
            clear();
            current_username = authentication_screen();
            
            if (current_username != NULL) {
                // Dapatkan player data
                PlayerData* player = get_player(current_username); 
                if (player != NULL) {
                    // Mulai game
                    unlock_levels_based_on_progress(current_username); 
                    selected_level = print_chapter_screen(current_username);
                }
            }
            break;
        case 2: // History
            // Implementasi fitur history
            break;
        case 3 :
            // Implementasi fitur leaderboard
            show_leaderboard();
            break;
        case 4: // How to play
            show_tutorial_screen();
            break;
        case 5: // Quit Game
            if (validate_QuitGame()) {
                showMsg_QuitGame();
            } else {
                menu_choice = 0;
            }
            break;
        }
    }

    stopBackgroundMusic();

    for (int i = 0; i < GroupCount; i++) {
        freeTree(ChapterTrees[i].ChapterTree, NULL); 
    }


    endwin();
    return 0;
}
