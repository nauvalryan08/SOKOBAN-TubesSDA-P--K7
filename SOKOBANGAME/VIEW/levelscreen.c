#include "levelscreen.h"
#include "../GAMEPLAY/GAME_LOGIC/GameStart.h"
#include <string.h>

#define MAX_LEVELS_PER_COLUMN 20
#define MAX_COLUMNS 5

static int current_selection = 0;
static int num_levels = 0;
static int current_column = 0;
static WINDOW* level_win = NULL;

void show_level_selection_screen() {
    if (level_win == NULL) {
        // Inisialisaisi ukuran layar window/ terminal untuk level choosing
        int height = LINES - 4;  // sisa 4 baris buat judul sama arah
        int width = COLS - 4;    // sisa 4 kolom buat judul sama arah
        int start_y = 3;         // mulai dari baris ke 3
        int start_x = 2;         // mulai dari kolom ke 2
        
        level_win = newwin(height, width, start_y, start_x);
        keypad(level_win, TRUE);
        curs_set(0);  // Hide cursor
    }
    
    // Display title
    attron(A_BOLD);
    mvprintw(1, (COLS - 20) / 2, "SELECT LEVEL");
    attroff(A_BOLD);
    
    // Hitung jumlah kolom yang dibutuhkan
    int total_columns = (num_levels + MAX_LEVELS_PER_COLUMN - 1) / MAX_LEVELS_PER_COLUMN;
    if (total_columns > MAX_COLUMNS) total_columns = MAX_COLUMNS;
    
    // Hitung lebar kolom (termasuk padding)
    int column_width = 25; // Sesuaikan dengan panjang nama level
    
    // Hapus konten level window
    werase(level_win);
    
    // Display level grid
    for (int col = 0; col < total_columns; col++) {
        int start_idx = col * MAX_LEVELS_PER_COLUMN;
        int end_idx = (col + 1) * MAX_LEVELS_PER_COLUMN;
        if (end_idx > num_levels) end_idx = num_levels;
        
        for (int i = start_idx; i < end_idx; i++) {
            int row = i % MAX_LEVELS_PER_COLUMN;
            int x_pos = col * column_width;
            int y_pos = row;
            
            // Highlight current selection
            if (i == current_selection) {
                wattron(level_win, A_STANDOUT);
            }
            
            // Format nomor level dengan leading zeros untuk alignment
            char level_num[4];
            snprintf(level_num, sizeof(level_num), "%02d", i + 1);
            
            mvwprintw(level_win, y_pos, x_pos, "%s: %s", level_num, ALL_LEVELS[i].level_name);
            
            if (i == current_selection) {
                wattroff(level_win, A_STANDOUT);
            }
        }
    }
    
    // Display instructions
    mvprintw(LINES - 2, 2, "Use ARROW keys to navigate, ENTER to select, ESC to quit");
    
    // Refresh hanya level window
    wrefresh(level_win);
    refresh();
}

LevelData* select_level() {
    int ch;
    num_levels = LEVEL_COUNT;
    current_selection = 0;
    current_column = 0;
    
    // Inisialisasi layar
    clear();
    curs_set(0);  // Hide cursor
  
    show_level_selection_screen();
    
    while (1) {
        // Tampilkan layar pilihan level awal
        show_level_selection_screen();
        
        ch = wgetch(level_win);
        
        switch (ch) {
            case KEY_LEFT:
                if (current_selection >= MAX_LEVELS_PER_COLUMN) {
                    current_selection -= MAX_LEVELS_PER_COLUMN;
                }
                break;
            case KEY_RIGHT:
                if (current_selection + MAX_LEVELS_PER_COLUMN < num_levels) {
                    current_selection += MAX_LEVELS_PER_COLUMN;
                }
                break;
            case KEY_UP:
                if (current_selection > 0) {
                    current_selection--;
                }
                break;
            case KEY_DOWN:
                if (current_selection < num_levels - 1) {
                    current_selection++;
                }
                break;
            case 10: // ENTER key
                delwin(level_win);
                level_win = NULL;
                curs_set(1);  // Show cursor
                return &ALL_LEVELS[current_selection];
            case 27:
                delwin(level_win);
                level_win = NULL;
                curs_set(1);  // Show cursor
                return NULL;
        }
    }
}

void display_level_info(LevelData* level) {
    clear();
    mvprintw(1, 2, "Level: %s", level->level_name);
    refresh();
    napms(1000); // Tampilkan info selama 1 detik
}

void run_level(LevelData* selected_level) {
    if (selected_level == NULL) return;
    
    RoomLayout room;
    start_level(&room, selected_level->map);
}

int handle_level_input() {
    int ch = getch();
    
    switch (ch) {
        case KEY_UP:
            return 1;
        case KEY_DOWN:
            return 2;
        case KEY_LEFT:
            return 3;
        case KEY_RIGHT:
            return 4;
        case 'r':
        case 'R':
            return 5;
        case 'u':
        case 'U':
            return 6;
        case 27:
            return 7; // Indicate quit
    }
    return 0;
}

