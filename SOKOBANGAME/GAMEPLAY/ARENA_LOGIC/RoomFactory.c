#include "RoomFactory.h"

//===============================================================//
//== Metod untuk parsing data objek pada Area ke dalam Struct  ==//
//===============================================================//
/* {Sopian} */

void parse_room(const char **map, RoomLayout *room) {
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

void print_room(const char **map, const RoomLayout *room) {
    int x, y, i;
    char tile;

    clear(); // Bersihkan layar

    // 1. Gambar arena dari map[] (tembok, lantai)
    for (y = 0; map[y] != NULL; y++) {
        for (x = 0; map[y][x] != '\0'; x++) {
            tile = map[y][x];
            // Mengabaikan karakter dinamis dari map 
            if (tile == '@' || tile == '$' || tile == '.' || tile == 'F') {
                mvaddch(y, x, ' ');
            } else {
                mvaddch(y, x, tile);
            }
        }
    }

    // 2. Gambar target (.)
    for (i = 0; i < room->target_count; i++) {
        mvaddch(room->targets[i].y, room->targets[i].x, '.');
    }

    // 3. Gambar box ($)
    for (i = 0; i < room->box_count; i++) {
        if (room->boxes[i].is_activated) {
            attron(COLOR_PAIR(2) | A_BOLD);
            mvaddch(room->boxes[i].y, room->boxes[i].x, '$');
            attroff(COLOR_PAIR(2) | A_BOLD);
        } else {
            attron(COLOR_PAIR(1) | A_BOLD);
            mvaddch(room->boxes[i].y, room->boxes[i].x, '$');
            attroff(COLOR_PAIR(1) | A_BOLD);
        }
    }

    // 4. Gambar finish (F)
    if (is_finish_activated(room)) {
        attron(COLOR_PAIR(2) | A_BOLD);
        mvaddch(room->finish.y, room->finish.x, 'F');
        attroff(COLOR_PAIR(2) | A_BOLD);
    } else {
        attron(COLOR_PAIR(3) | A_DIM);
        mvaddch(room->finish.y, room->finish.x, 'F');
        attroff(COLOR_PAIR(3) | A_DIM);
    }

    // 5. Gambar player (@)
    mvaddch(room->player.y, room->player.x, '@');

    mvprintw(35, 50, "%d",room->box_count);

    refresh(); // Tampilkan ke layar
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