#ifndef ROOMFACTORY_H
#define ROOMFACTORY_H

#include "../../UTILS/include/boolean.h"
#include "../../UTILS/include/curses.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_OBJECTS 15

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
void parse_room(const char **map, RoomLayout *room);

//===================================//
//==>  Menghasilkan Output Arena  <==//
//===================================//
/* {Sopian} */
void print_room(const char **map, const RoomLayout *room);

//================================================//
//==>  Memeriksa apakah semua box sudah Aktif  <==//
//================================================//
/* {Sopian} */
boolean is_finish_activated(const RoomLayout *room);


#endif