#include "RoomFactory.h"


//===============================================================//
//== Metod untuk parsing data objek pada Area ke dalam Struct  ==//
//===============================================================//
/* {Sopian} */

void parse_room(RoomLayout *room, const char **map) {
    int x, y;

    room->box_count = 0;
    room->target_count = 0;

    for (y = 0 ; map[y] != NULL ; y++) {
        for (x = 0 ; map[y][x] != '\0'; x++) {
            char tile = map[y][x];

            switch (tile) {
                case '@' :
                    room->player = (Object){x,y, false};
                    break;
                case '$' :
                    room->boxes[room->box_count++] = (Object){x, y, false};
                    break;
                case '.' :
                    room->targets[room->target_count++] = (Object){x,y,false};
                    break;
                case 'F' :
                    room->finish = (Object){x,y,false};
                    break;
            }
        }
    }
}

//=============================================//
//== Memeriksa apakah box sudah aktif semua  ==//
//=============================================//
/* {Sopian} */

boolean is_finish_activated(const RoomLayout *room) {
    int i;
    for (i = 0; i < room->box_count; i++) {
        if (!room->boxes[i].is_activated) {
            return false;
        }
    }
    return true;
}

// ==> memeriksa jumlah box activated
int count_active_box(const RoomLayout *room) {
    int count = 0;
    for (int i = 0; i < room->box_count; i++) {
        if (room->boxes[i].is_activated) {
            count++;
        }
    }
    return count;
}

//===========================================================//
//== Menghasilkan Output Arena sesuai data map dan Layout  ==//
//===========================================================//
/* {Sopian} */

//==>  SIMBOL OBJECT & ICON  <==//


//================================>

void print_room(const char *name, const char **map, const RoomLayout *room) {
    int x, y, i, dy, dx, dy_tile, dx_tile;
    char tile;

    curs_set(0); // Hide the cursor

    int min_height = 20;
    int min_width = 50;

    // Hitung ukuran map
    int map_height = 0;
    int map_width = 0;
    for (y = 0; map[y] != NULL; y++) {
        int row_len = strlen(map[y]);
        if (row_len > map_width) map_width = row_len;
        map_height++;
    }
 
    // Hitung ukuran arena dalam pixel terminal
    int arena_height = map_height * TILE_HEIGHT;
    int arena_width = map_width * TILE_WIDTH;

    clear();

    // // Tampilkan ukuran terminal
    // char size_info[50];
    // snprintf(size_info, sizeof(size_info), "Terminal: %d x %d", COLS, LINES);
    // mvprintw(0, 0, "%s", size_info);

    if (LINES < map_height || LINES < min_height || COLS < map_width || COLS < min_width) {
        const char *msg = "Please resize terminal to fit the arena";
        int msg_y = LINES / 2;
        int msg_x = (COLS - strlen(msg)) / 2;
        mvprintw(msg_y, msg_x > 0 ? msg_x : 0, "%s", msg);
        refresh();
        return;
    }

    int offset_y = (LINES - arena_height) / 2;
    int offset_x = (COLS - arena_width) / 2;

    print_header(name);
    print_sidebar(room, 0, 0); // Ganti 0,0 kalau kamu punya timer dan skor sebenarnya
    print_bottom_bar(); 

    // Gambar map
    for (y = 0; map[y] != NULL; y++) {
        for (x = 0; map[y][x] != '\0'; x++) {
            tile = map[y][x];
            dy = offset_y + y*TILE_HEIGHT;
            dx = offset_x + x*TILE_WIDTH;

            if (tile == '#') {
                // mvaddch(dy, dx, '\xB0');
                // mvaddch(dy, dx + 1, '\xB0');
                // mvaddch(dy, dx + 2, '\xB0');
                for (dy_tile = 0; dy_tile < TILE_HEIGHT; dy_tile++) {
                    for (dx_tile = 0; dx_tile < TILE_WIDTH; dx_tile++) {
                        mvaddch(dy + dy_tile, dx + dx_tile, '\xB0');  // karakter ASCII semi-blok
                    }
                }
            }
        }
    }

    // Target
    for (i = 0; i < room->target_count; i++) {
        attron(COLOR_PAIR(4) | A_BOLD);
        // mvprintw(offset_y + room->targets[i].y, offset_x + room->targets[i].x*TILE_WIDTH + 1, "\xFA");
        dx = offset_x + room->targets[i].x * TILE_WIDTH + TILE_WIDTH / 2;
        dy = offset_y + room->targets[i].y * TILE_HEIGHT + TILE_HEIGHT / 2;
        mvprintw(dy, dx, "\xFA");
        attroff(COLOR_PAIR(4) | A_BOLD);
    }

    // Box
    for (i = 0; i < room->box_count; i++) {
        attron((room->boxes[i].is_activated ? COLOR_PAIR(2) : COLOR_PAIR(5)));
        // mvprintw(offset_y + room->boxes[i].y, offset_x + room->boxes[i].x*TILE_WIDTH, "\xFE");
        // mvprintw(offset_y + room->boxes[i].y, offset_x + room->boxes[i].x*TILE_WIDTH + 1, "\xFE");
        dx = offset_x + room->boxes[i].x * TILE_WIDTH + TILE_WIDTH / 2;
        dy = offset_y + room->boxes[i].y * TILE_HEIGHT + TILE_HEIGHT / 2;
        mvprintw(dy, dx, "\xFE");

        // mvprintw(offset_y + room->boxes[i].y, offset_x + room->boxes[i].x*TILE_WIDTH + 2, "\xFE");
        attroff(COLOR_PAIR(2));
        attroff(COLOR_PAIR(4));
    }

    // Finish
    attron(is_finish_activated(room) ? (COLOR_PAIR(2) | A_BOLD) : (COLOR_PAIR(3) | A_DIM));
    // mvaddch(offset_y + room->finish.y, offset_x + room->finish.x*TILE_WIDTH + 1, 'F');
    dx = offset_x + room->finish.x * TILE_WIDTH + TILE_WIDTH / 2;
    dy = offset_y + room->finish.y * TILE_HEIGHT + TILE_HEIGHT / 2;
    mvaddch(dy,dx, 'F');
    attroff(COLOR_PAIR(2) | A_BOLD);
    attroff(COLOR_PAIR(3) | A_DIM);

    // Player
    // mvaddch(offset_y + room->player.y, offset_x + room->player.x*TILE_WIDTH + 1, '@');
    dx = offset_x + room->player.x * TILE_WIDTH + TILE_WIDTH / 2;
    dy = offset_y + room->player.y * TILE_HEIGHT + TILE_HEIGHT / 2;
    mvaddch(dy,dx, '@');


    refresh();
}

//======================================================================//
//== Menghasilkan Output Outer seeperti Navigasi, Hiasan, nama level  ==//
//======================================================================//
/* {Sopian} */

void print_centered_text(int y, const char *text) {
    int x = (COLS - strlen(text)) / 2;
    mvprintw(y, x, "%s", text);
}

void print_header(const char *level_name) {
    char border[COLS + 1];
    memset(border, '=', COLS);
    border[COLS] = '\0';

    attron(A_BOLD);
    mvprintw(1, 0, "%s", border);

    print_centered_text(2, level_name);

    mvprintw(3, 0, "%s", border);
    attroff(A_BOLD);
}


void print_sidebar(const RoomLayout *room, int timer, int score) {
    int sidebar_width = 24;
    int start_y = 4;  // Mulai di bawah header
    int end_y = LINES - 5; // Berhenti sebelum bottom bar
    int current_y = start_y;
    
    // Warna dan atribut untuk sidebar
    int border_color = COLOR_PAIR(6);  // Asumsikan COLOR_PAIR(6) sudah didefinisikan
    int text_color = COLOR_PAIR(7) | A_BOLD;
    
    // Gambar border kiri
    for (current_y = start_y; current_y <= end_y; current_y++) {
        attron(border_color);
        mvaddch(current_y, 0, ACS_VLINE);
        mvaddch(current_y, sidebar_width + 1, ACS_VLINE);
        attroff(border_color);
    }
    
    // Header sidebar
    attron(border_color);
    mvaddch(start_y, 0, ACS_ULCORNER);
    mvaddch(start_y, sidebar_width + 1, ACS_URCORNER);
    for (int i = 1; i <= sidebar_width; i++) {
        mvaddch(start_y, i, ACS_HLINE);
    }
    attroff(border_color);
    
    attron(text_color);
    mvprintw(start_y + 1, 2, "#====================#");
    mvprintw(start_y + 2, 2, "|     GAME STATUS    |");
    mvprintw(start_y + 3, 2, "#====================#");
    
    attroff(text_color);
    
    // Konten sidebar
    current_y = start_y + 5;
    
    attron(text_color);
    mvprintw(current_y++, 2, "+--------------------+");
    mvprintw(current_y, 2, "| Boxes :");
    mvprintw(current_y, 23, "|");
    mvprintw(current_y++, 12, "%d /%2d", count_active_box(room), room->box_count);
    mvprintw(current_y++, 2, "+--------------------+");
    mvprintw(current_y, 2, "| Time  :");
    mvprintw(current_y, 23, "|");
    mvprintw(current_y++, 12, "%02d:%02d", timer/60, timer%60);
    mvprintw(current_y++, 2, "+--------------------+");
    mvprintw(current_y, 2, "| Score :");
    mvprintw(current_y, 23, "|");
    mvprintw(current_y++, 12, "%d", score);
    mvprintw(current_y++, 2, "+--------------------+");

    current_y++;
    mvprintw(current_y++, 2, "+--------------------+");
    mvprintw(current_y, 2, "| Undo :");
    mvprintw(current_y, 23, "|");
    mvprintw(current_y++, 12, "%d", score);
    mvprintw(current_y++, 2, "+--------------------+");

    attroff(text_color);
    
    // Footer sidebar
    attron(border_color);
    mvaddch(end_y, 0, ACS_LLCORNER);
    mvaddch(end_y, sidebar_width + 1, ACS_LRCORNER);
    for (int i = 1; i <= sidebar_width; i++) {
        mvaddch(end_y, i, ACS_HLINE);
    }
    attroff(border_color);
    
    // Tambahkan beberapa dekorasi
    attron(COLOR_PAIR(8));
    for (int y = start_y + 18; y < end_y - 2; y += 2) {
        mvaddch(y, sidebar_width - 2, ACS_DIAMOND);
    }
    attroff(COLOR_PAIR(8));
}




void print_bottom_bar() {
    attron(A_REVERSE | A_BOLD);
    print_centered_text(LINES - 4, " ARROW_KEYS : Move | ESC : Quit | R : Restart | U : Undo ");
    attroff(A_REVERSE | A_BOLD);
}