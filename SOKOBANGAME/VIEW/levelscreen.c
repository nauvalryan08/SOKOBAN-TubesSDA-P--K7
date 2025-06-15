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
    
    while (1) {
        show_level_selection_screen(levels, count);
        
        ch = wgetch(level_win);
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
                return NULL;
        }
        pthread_join(arrowSound, NULL);
        refresh();
    }
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

// Chapter 1 levels selection
LevelData* select_level_chapter1() {
    initChapter1();
    LevelData* chapter1[30];

    // static LevelData* chapter1[30];
    LevelCollector collector = {.count =  0};

    active_collector = &collector;
    levelOrderTraversal(ChapterTrees[CHAPTER1].ChapterTree, store_callback_wrapper);
    active_collector = NULL;

    for (int i = 0; i < collector.count; i++) {
        chapter1[i] = collector.array[i];
    }

    return select_level_from_list(chapter1, collector.count);
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