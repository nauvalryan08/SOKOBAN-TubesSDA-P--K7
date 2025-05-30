#include "RoomFactory.h"

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


void print_room(const char **map, const RoomLayout *room) {
    clear(); // Bersihkan layar

    // 1. Gambar arena dari map[] (tembok, lantai)
    for (int y = 0; map[y] != NULL; y++) {
        for (int x = 0; map[y][x] != '\0'; x++) {
            char tile = map[y][x];
            // Abaikan karakter dinamis dari map (optional)
            if (tile == '@' || tile == '$' || tile == '.' || tile == 'F') {
                mvaddch(y, x, ' ');
            } else {
                mvaddch(y, x, tile);
            }
        }
    }

    // 2. Gambar target (.)
    for (int i = 0; i < room->target_count; i++) {
        mvaddch(room->targets[i].y, room->targets[i].x, '.');
    }

    // 3. Gambar box ($)
    for (int i = 0; i < room->box_count; i++) {
        mvaddch(room->boxes[i].y, room->boxes[i].x, '$');
    }

    // 4. Gambar finish (F)
    mvaddch(room->finish.y, room->finish.x, 'F');

    // 5. Gambar player (@)
    mvaddch(room->player.y, room->player.x, '@');

    refresh(); // Tampilkan ke layar
}
