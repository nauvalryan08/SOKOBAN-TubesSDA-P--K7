#define NCURSES_MOUSE_VERSION
#include "LevelScreen.h"
#include "levelscreen.h"
#include <string.h>

#define MAX_LEVELS_PER_COLUMN 20
#define MAX_COLUMNS 5

static int current_selection = 0;
static int num_levels = 0;
static int current_column = 0;
static WINDOW* level_win = NULL;

typedef struct{
    LevelData *array[100];
    int count;
}LevelCollector;

void store_level_data (void* data, LevelCollector *collector) {
    if (collector->count < 100) { // Sesuaikan batas maksimal level
        collector->array[collector->count++] = (LevelData *)data;
    }
}

static LevelCollector *active_collector = NULL;

void store_callback_wrapper (void* data) {
    store_level_data(data, active_collector);
}

// Helper function to display level selection screen
void show_level_selection_screen(LevelData* levels[], int count) {
    if (level_win == NULL) {
        int height = LINES - 4;
        int width = COLS - 4;
        int start_y = 3;
        int start_x = 2;
        
        level_win = newwin(height, width, start_y, start_x);
        keypad(level_win, TRUE);
        curs_set(0);
    }
    
    attron(A_BOLD);
    mvprintw(1, (COLS - 20) / 2, "SELECT LEVEL");
    attroff(A_BOLD);
    
    int total_columns = (count + MAX_LEVELS_PER_COLUMN - 1) / MAX_LEVELS_PER_COLUMN;
    if (total_columns > MAX_COLUMNS) total_columns = MAX_COLUMNS;
    
    int column_width = 25;
    
    werase(level_win);
    
    for (int col = 0; col < total_columns; col++) {
        int start_idx = col * MAX_LEVELS_PER_COLUMN;
        int end_idx = (col + 1) * MAX_LEVELS_PER_COLUMN;
        if (end_idx > count) end_idx = count;
        
        for (int i = start_idx; i < end_idx; i++) {
            int row = i % MAX_LEVELS_PER_COLUMN;
            int x_pos = col * column_width;
            int y_pos = row;
            
            if (i == current_selection) {
                wattron(level_win, A_STANDOUT);
            } else {
                if (!levels[i]->is_unlocked) {
                    wattron(level_win, COLOR_PAIR(3)); // Locked
                } else if (levels[i]->is_finished) {
                    wattron(level_win, COLOR_PAIR(2)); // Finished
                } else {
                    wattron(level_win, COLOR_PAIR(1)); // Default
                }
            }
            
            char level_num[4];
            snprintf(level_num, sizeof(level_num), "%02d", i + 1);
            
            mvwprintw(level_win, y_pos, x_pos, "%s: %s", level_num, levels[i]->level_name);
            
            if (i == current_selection) {
                wattroff(level_win, A_STANDOUT);
            } else {
                wattroff(level_win, COLOR_PAIR(1));
                wattroff(level_win, COLOR_PAIR(2));
                wattroff(level_win, COLOR_PAIR(3));
            }
        }
    }
    
    wrefresh(level_win);
    refresh();
}

// Generic level selection function
LevelData* select_level_from_list(LevelData* levels[], int count) {
    int ch;
    num_levels = count;
    current_selection = 0;
    current_column = 0;
    
    clear();
    curs_set(0);
  
    show_level_selection_screen(levels, count);
    
    while ((ch = getch()) != 27) {
        show_level_selection_screen(levels, count);
        pthread_t arrowSound;

        switch (ch) {
            case KEY_LEFT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if (current_selection >= MAX_LEVELS_PER_COLUMN) {
                    current_selection -= MAX_LEVELS_PER_COLUMN;
                }
                break;
            case KEY_RIGHT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if (current_selection + MAX_LEVELS_PER_COLUMN < num_levels) {
                    current_selection += MAX_LEVELS_PER_COLUMN;
                }
                break;
            case KEY_UP:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if (current_selection > 0) {
                    current_selection--;
                }
                break;
            case KEY_DOWN:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                if (current_selection < num_levels - 1) {
                    current_selection++;
                }
                break;
            case 10: // ENTER key
                delwin(level_win);
                level_win = NULL;
                curs_set(1);
                return levels[current_selection];
            case 27:
                endwin();
                delwin(level_win);
                level_win = NULL;
                curs_set(1);
                pthread_t enterSound;
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                pthread_join(enterSound, NULL);
        }
        pthread_join(arrowSound, NULL);
        refresh();
    }
    return NULL;
}

// Tutorial levels selection
LevelData* select_level_tutorial() {
    initTutorial();
    LevelData* chapterTutorial[30];

    // static LevelData* chapter1[30];
    LevelCollector collector = {.count =  0};

    active_collector = &collector;
    levelOrderTraversal(ChapterTrees[TUTORIAL].ChapterTree, store_callback_wrapper);
    active_collector = NULL;

    for (int i = 0; i < collector.count; i++) {
        chapterTutorial[i] = collector.array[i];
    }

    return select_level_from_list(chapterTutorial, collector.count);
}

// Chapter 2 levels selection
LevelData* select_level_chapter2() {
    initChapter2();
    LevelData* chapter2[30];

    // static LevelData* chapter2[30];
    LevelCollector collector = {.count =  0};

    active_collector = &collector;
    levelOrderTraversal(ChapterTrees[CHAPTER2].ChapterTree, store_callback_wrapper);
    active_collector = NULL;

    for (int i = 0; i < collector.count; i++) {
        chapter2[i] = collector.array[i];
    }

    return select_level_from_list(chapter2, collector.count);
}

// Chapter 3 levels selection
LevelData* select_level_chapter3() {
    initChapter3();
    LevelData* chapter3[30];

    // static LevelData* chapter3[30];
    LevelCollector collector = {.count =  0};

    active_collector = &collector;
    levelOrderTraversal(ChapterTrees[CHAPTER3].ChapterTree, store_callback_wrapper);
    active_collector = NULL;

    for (int i = 0; i < collector.count; i++) {
        chapter3[i] = collector.array[i];
    }

    return select_level_from_list(chapter3, collector.count);
}

// Chapter 4 levels selection
LevelData* select_level_chapter4() {
    initChapter4();
    LevelData* chapter4[30];

    // static LevelData* chapter4[30];
    LevelCollector collector = {.count =  0};

    active_collector = &collector;
    levelOrderTraversal(ChapterTrees[CHAPTER4].ChapterTree, store_callback_wrapper);
    active_collector = NULL;

    for (int i = 0; i < collector.count; i++) {
        chapter4[i] = collector.array[i];
    }

    return select_level_from_list(chapter4, collector.count);
}

// Chapter 5 levels selection
LevelData* select_level_chapter5() {
    initChapter5();
    LevelData* chapter5[30];

    // static LevelData* chapter5[30];
    LevelCollector collector = {.count =  0};

    active_collector = &collector;
    levelOrderTraversal(ChapterTrees[CHAPTER5].ChapterTree, store_callback_wrapper);
    active_collector = NULL;

    for (int i = 0; i < collector.count; i++) {
        chapter5[i] = collector.array[i];
    }

    return select_level_from_list(chapter5, collector.count);
}

// Original select_level function (all levels)
LevelData* select_level() {
    static LevelData* level_ptrs[LEVEL_COUNT];
    for (int i = 0; i < LEVEL_COUNT; i++) {
        level_ptrs[i] = &ALL_LEVELS[i];
    }
    return select_level_from_list(level_ptrs, LEVEL_COUNT);
}

LevelData* chapter1_screen(){
    int ch;
    mmask_t old;
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, &old);
    MEVENT event;
    current_selection = 0;
    initChapter1();
    LevelData* chapter1[9];
    LevelCollector collector = {.count = 0};
    active_collector = &collector;
    levelOrderTraversal(ChapterTrees[CHAPTER1].ChapterTree, store_callback_wrapper);
    for (int i = 0; i < collector.count; i++){
        chapter1[i] = collector.array[i];
    }

    clear();
    curs_set(0);
    while ((ch = getch()) != 27) {
        pthread_t arrowSound, enterSound;
        // Create buttons with proper proportions
        Button levels[] = {
            {COLS/2-5, LINES/2-12, 21, 4, "Level 1"}, // n1
            {COLS/2-45, LINES/2-5, 21, 4, "Level 2"}, // n2
            {COLS/2+35, LINES/2-5, 21, 4, "Level 3"}, // n3
            {COLS/2-65, LINES/2+2, 21, 4, "Level 4"},   // n4
            {COLS/2-25, LINES/2+2, 21, 4, "Level 5"},   // n5
            {COLS/2+10, LINES/2+2, 21, 4, "Level 6"},   // n6
            {COLS/2+35, LINES/2+2, 21, 4, "Level 7"},   // n7
            {COLS/2+60, LINES/2+2, 21, 4, "Level 8"},   // n8
        };

        // Display instructions
        mvprintw(1, 1, "Klik kiri pada tombol level untuk memilih level!");
        mvprintw(2, 1, "Atau gunakan tombol panah kiri/kanan untuk navigasi");
        mvprintw(3, 1, "Gunakan tombol ESC untuk kembali ke menu utama");
        mvprintw(4, 1, "Tekan ENTER untuk memilih level");

        // Display buttons
        for (int i = 0; i < collector.count; i++) {
            if (i == current_selection) {
                attron(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            } else {
                if (!chapter1[i]->is_unlocked) {
                    attron(COLOR_PAIR(4)); // Gray for locked levels
                } else if (chapter1[i]->is_finished) {
                    attron(COLOR_PAIR(2)); // Green for finished levels
                } else {
                    attron(COLOR_PAIR(1)); // White for unlocked but not finished
                }
            }
            draw_btn(&levels[i]);
            if (i == current_selection) {
                attroff(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            } else {
                attroff(COLOR_PAIR(COLOR_RED));
                attroff(COLOR_PAIR(2));
                attroff(COLOR_PAIR(3));
            }
        }

        // Draw tree connections
        int ch1_connectorindex[] = {-1, 0, 0, 1, 1, 2, 2, 2};
        draw_tree_connections(levels, ch1_connectorindex, collector.count);

        switch (ch) {
            case KEY_LEFT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                current_selection = (current_selection > 0) ? current_selection - 1 : collector.count - 1;
                break;
            case KEY_RIGHT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                current_selection = (current_selection < collector.count - 1) ? current_selection + 1 : 0;
                break;
            case KEY_ENTER:
            case '\n':
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                return chapter1[current_selection];
                break;
            case KEY_MOUSE:
                if (getmouse(&event) == OK) {
                    if (event.bstate & BUTTON1_CLICKED){
                        pthread_create(&enterSound, NULL, playEnterSound, NULL);
                        for (int i = 0; i < collector.count; i++) {
                            if (isbtnarea(&levels[i], event.x, event.y)) {
                                    current_selection = i;
                            }
                        }
                    }
                }
            case KEY_RESIZE:
                resize_term(0,0);
                break;
        }
        pthread_join(arrowSound, NULL);
        pthread_join(enterSound, NULL);
        refresh();
    }
    return NULL;
}

LevelData* chapter2_screen(){
    int ch;
    mmask_t old;
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, &old);
    MEVENT event;
    current_selection = 0;
    initChapter2();
    LevelData* chapter2[16]; // 15 levels + 1 bonus level

    LevelCollector collector = {.count = 0};
    active_collector = &collector;
    levelOrderTraversal(ChapterTrees[CHAPTER2].ChapterTree, store_callback_wrapper);
    for (int i = 0; i < collector.count; i++){
        chapter2[i] = collector.array[i];
    }

    clear();
    curs_set(0);
    while ((ch = getch()) != 27) {
        pthread_t arrowSound, enterSound;
        // Create buttons with proper proportions
        Button levels[] = {
            {COLS/2-15, LINES/2-16, 21, 4, "Level 1"},    // n1
            {COLS/2-60, LINES/2-10, 21, 4, "Level 2"}, // n2
            {COLS/2-15, LINES/2-10, 21, 4, "Level 3"},    // n3
            {COLS/2+30, LINES/2-10, 21, 4, "Level 4"}, // n4
            {COLS/2-75, LINES/2-2, 21, 4, "Level 5"},    // n5
            {COLS/2-40, LINES/2-2, 21, 4, "Level 6"},    // n6
            {COLS/2-10, LINES/2-2, 21, 4, "Level 7"},    // n7
            {COLS/2+20, LINES/2-2, 21, 4, "Level 8"},    // n8
            {COLS/2-90, LINES/2+8, 21, 4, "Level 9"}, // n9
            {COLS/2-60, LINES/2+8, 21, 4, "Level 10"},// n10
            {COLS/2-30, LINES/2+8, 21, 4, "Level 11"},   // n11
            {COLS/2, LINES/2+8, 21, 4, "Level 12"},// n12
            {COLS/2+30, LINES/2+8, 21, 4, "Level 13"},// n13
            {COLS/2+60, LINES/2+8, 21, 4, "Level 14"},// n14
            {(COLS/2+30)+23, LINES/2-2, 21, 4, "Level 15"},// n15
            {(COLS/2+60)+23, LINES/2+8, 10, 2, "Bonus"},   // B1
        };

        // Display instructions
        mvprintw(1, 1, "Klik kiri pada tombol level untuk memilih level!");
        mvprintw(2, 1, "Atau gunakan tombol panah kiri/kanan untuk navigasi");
        mvprintw(3, 1, "Gunakan tombol ESC untuk kembali ke menu utama");
        mvprintw(4, 1, "Tekan ENTER untuk memilih level");

        // Display buttons
        for (int i = 0; i < collector.count; i++) {
            if (i == current_selection) {
                attron(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            } else {
                if (!chapter2[i]->is_unlocked) {
                    attron(COLOR_PAIR(COLOR_RED)); // Gray for locked levels
                } else if (chapter2[i]->is_finished) {
                    attron(COLOR_PAIR(2)); // Green for finished levels
                } else {
                    attron(COLOR_PAIR(1)); // White for unlocked but not finished
                }
            }
            draw_btn(&levels[i]);
            if (i == current_selection) {
                attroff(A_REVERSE | COLOR_PAIR(COLOR_GREEN));
            } else {
                attroff(COLOR_PAIR(COLOR_RED));
                attroff(COLOR_PAIR(2));
                attroff(COLOR_PAIR(3));
            }
        }

        // Draw tree connections based on Chapter 2's structure
        int ch2_connectorindex[] = {
            -1,  // Level 1 (root)
            0,   // Level 2 (child of 1)
            0,   // Level 3 (child of 1)
            0,   // Level 4 (child of 1)
            1,   // Level 5 (child of 2)
            1,   // Level 6 (child of 2)
            2,   // Level 7 (child of 3)
            2,   // Level 8 (child of 3)
            4,   // Level 9 (child of 5)
            4,   // Level 10 (child of 5)
            4,   // Level 11 (child of 5)
            5,   // Level 12 (child of 6)
            5,   // Level 13 (child of 6)
            6,   // Level 14 (child of 7)
            3,   // Level 15 (child of 4)
            14   // Bonus (child of 15)
        };
        draw_tree_connections(levels, ch2_connectorindex, collector.count);

        switch (ch) {
            case KEY_LEFT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                current_selection = (current_selection > 0) ? current_selection - 1 : collector.count - 1;
                break;
            case KEY_RIGHT:
                pthread_create(&arrowSound, NULL, playArrowSound, NULL);
                current_selection = (current_selection < collector.count - 1) ? current_selection + 1 : 0;
                break;
            case KEY_ENTER:
            case '\n':
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                return chapter2[current_selection];
                break;
            case KEY_MOUSE:
                if (getmouse(&event) == OK) {
                    if (event.bstate & BUTTON1_CLICKED){
                        pthread_create(&enterSound, NULL, playEnterSound, NULL);
                        for (int i = 0; i < collector.count; i++) {
                            if (isbtnarea(&levels[i], event.x, event.y)) {
                                    current_selection = i;
                            }
                        }
                    }
                }
            case KEY_RESIZE:
                resize_term(0,0);
                break;
        }
        pthread_join(arrowSound, NULL);
        pthread_join(enterSound, NULL);
        refresh();
    }
    return NULL;
}

void display_level_info(LevelData* level) {
    clear();
    mvprintw(1, 2, "Level: %s", level->level_name);
    refresh();
    napms(1000);
}

void run_level(LevelData* selected_level, ChapterData* current_chapter, const char* username) {
    if (selected_level == NULL) return;

    clear();
    
    RoomLayout room;

    //Memeriksa apakah stage dapat di akses
    if (!selected_level->is_unlocked) {

        draw_centered_text( LINES/2 , 0, COLS, "This Stage is locked, please finish previous stage!");
        draw_centered_text(LINES/2 + 1, 0, COLS, "[Press ENTER to continue...]");

        refresh();

        pthread_t invalidSound;
        pthread_create(&invalidSound, NULL, playInvalidSound, NULL);
        pthread_detach(invalidSound);

        int ch;
        do {
            ch = getch();
            if (ch == '\n' || ch == '\r' || ch == 10) {
                pthread_t enterSound;
                pthread_create(&enterSound, NULL, playEnterSound, NULL);
                pthread_detach(enterSound);
            }
        } while (ch != '\n' && ch != '\r' && ch != 10); // ENTER key

        return;
    }

    //memulai jika dapat diakses
    start_level(&room, selected_level, current_chapter, username);
}