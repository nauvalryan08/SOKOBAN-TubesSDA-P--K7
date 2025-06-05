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


//===========================================================//
//== Menghasilkan Output Arena sesuai data map dan Layout  ==//
//===========================================================//
/* {Sopian} */

//==>  SIMBOL OBJECT & ICON  <==//


//================================>

void print_room(const char **map, const RoomLayout *room) {
    int x, y, i;
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
    map_width *= 3;

    clear();

    // Tampilkan ukuran terminal
    char size_info[50];
    snprintf(size_info, sizeof(size_info), "Terminal: %d x %d", COLS, LINES);
    mvprintw(0, 0, "%s", size_info);

    if (LINES < map_height || LINES < min_height || COLS < map_width || COLS < min_width) {
        const char *msg = "Please resize terminal to fit the arena";
        int msg_y = LINES / 2;
        int msg_x = (COLS - strlen(msg)) / 2;
        mvprintw(msg_y, msg_x > 0 ? msg_x : 0, "%s", msg);
        refresh();
        return;
    }

    int offset_y = (LINES - map_height) / 2;
    int offset_x = (COLS - map_width) / 2;

    // Gambar map
    for (y = 0; map[y] != NULL; y++) {
        for (x = 0; map[y][x] != '\0'; x++) {
            tile = map[y][x];
            int dy = offset_y + y;
            int dx = offset_x + x*3;

            if (tile == '#') {
                mvaddch(dy, dx, '\xB0');
                mvaddch(dy, dx + 1, '\xB0');
                mvaddch(dy, dx + 2, '\xB0');

            }
        }
    }

    // Target
    for (i = 0; i < room->target_count; i++) {
        attron(COLOR_PAIR(4) | A_BOLD);
        mvprintw(offset_y + room->targets[i].y, offset_x + room->targets[i].x*3 + 1, "\xFA");
        attroff(COLOR_PAIR(4) | A_BOLD);
    }

    // Box
    for (i = 0; i < room->box_count; i++) {
        attron((room->boxes[i].is_activated ? COLOR_PAIR(2) : COLOR_PAIR(5)));
        mvprintw(offset_y + room->boxes[i].y, offset_x + room->boxes[i].x*3, "\xB2");
        mvprintw(offset_y + room->boxes[i].y, offset_x + room->boxes[i].x*3 + 1, "\xB2");
        mvprintw(offset_y + room->boxes[i].y, offset_x + room->boxes[i].x*3 + 2, "\xB2");
        attroff(COLOR_PAIR(2));
        attroff(COLOR_PAIR(4));
    }

    // Finish
    attron(is_finish_activated(room) ? (COLOR_PAIR(2) | A_BOLD) : (COLOR_PAIR(3) | A_DIM));
    mvaddch(offset_y + room->finish.y, offset_x + room->finish.x*3 + 1, 'F');
    attroff(COLOR_PAIR(2) | A_BOLD);
    attroff(COLOR_PAIR(3) | A_DIM);

    // Player
    mvaddch(offset_y + room->player.y, offset_x + room->player.x*3 + 1, '@');

    refresh();
}


//=============================================//
//== Memeriksa apakah box sudah aktif semua  ==//
//=============================================//
/* {Sopian} */

boolean is_finish_activated(const RoomLayout *room) {
    for (int i = 0; i < room->box_count; i++) {
        if (!room->boxes[i].is_activated) {
            return false;
        }
    }
    return true;
}