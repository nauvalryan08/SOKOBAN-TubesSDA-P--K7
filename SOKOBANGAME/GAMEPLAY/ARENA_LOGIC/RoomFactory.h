#ifndef ROOMFACTORY_H
#define ROOMFACTORY_H

#include "../../UTILS/include/boolean.h"
#include "../../UTILS/include/curses.h"
#include "../../VIEW/viewtoolkit.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_OBJECTS 50

#define TILE_WIDTH 4  // Ukuran horizontal setiap tile
#define TILE_HEIGHT 2    // Tinggi vertikal 1 tile (spasi ke bawah)

//================================//
//==>  STRUCT OBJECT & LAYOUT  <==//
//================================//
/* {Sopian} */

typedef struct {
    int x, y;
    boolean is_activated;
} Object;

typedef struct {
    Object player;
    Object boxes[MAX_OBJECTS];
    int box_count;
    Object targets[MAX_OBJECTS];
    int target_count;
    Object finish;
} RoomLayout;


//===============================================================//
//==>  Method untuk menyimpan data objek pad arena ke struct  <==//
//===============================================================//
/* {Sopian} */
void parse_room(RoomLayout* room, const char **map);

//===================================//
//==>  Menghasilkan Output Arena  <==//
//===================================//
/* {Sopian} */

void print_room(const char *name, const char **map, const RoomLayout *room, Button *btn);

void print_header(const char *level_name);

void print_sidebar(const RoomLayout *room, int timer, int score);

void print_bottom_bar();

//================================================//
//==>  Memeriksa apakah semua box sudah Aktif  <==//
//================================================//
/* {Sopian} */
boolean is_finish_activated(const RoomLayout *room);

int count_active_box(const RoomLayout *room);



#endif