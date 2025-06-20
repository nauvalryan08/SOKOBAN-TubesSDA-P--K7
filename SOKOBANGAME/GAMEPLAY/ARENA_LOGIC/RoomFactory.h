#ifndef ROOMFACTORY_H
#define ROOMFACTORY_H

#include "../../UTILS/include/boolean.h"
#include "../../UTILS/include/curses.h"
#include "../../VIEW/viewtoolkit.h"
#include "../GAME_LOGIC/ScoreGame.h"

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
    Boolean is_activated;
} Object;

typedef struct {
    Object player;
    Object boxes[MAX_OBJECTS];
    int box_count;
    Object targets[MAX_OBJECTS];
    int target_count;
    Object finish;
} RoomLayout;

/**********************************************/
/* -->          Getter AND Setter         <-- */
/**********************************************/

// ==> getter Objek;

int getObject_X (Object object);
int getObject_Y (Object object);
int getObject_Status (Object object);

// ==> setter Objek;

void setObject_X(Object *object, int x);
void setObject_Y(Object *object, int y);
void setObject_Status(Object *object, Boolean status);
void setObject_Var(Object *object, int x, int y, Boolean status);

// ==> getter RoomLayout
Object getPlayer (RoomLayout room);
Object getBoxes (RoomLayout room, int i);
int getBoxCount (RoomLayout room);
Object getTargets (RoomLayout room, int i);
int getTargetsCount (RoomLayout room);
Object getFinish (RoomLayout room);


//===============================================================//
//==>  Method untuk menyimpan data objek pad arena ke struct  <==//
//===============================================================//
/* {Sopian} */
void parse_room(RoomLayout* room, const char **map);

//===================================//
//==>  Menghasilkan Output Arena  <==//
//===================================//
/* {Sopian} */

void print_room(const char *name, const char **map, const RoomLayout *room, ScoreData scoreData, Button *btn);

void print_header(const char *level_name);

void print_sidebar(const RoomLayout *room, ScoreData data);

void print_bottom_bar();

//================================================//
//==>  Memeriksa apakah semua box sudah Aktif  <==//
//================================================//
/* {Sopian} */
Boolean is_finish_activated(const RoomLayout *room);

int count_active_box(const RoomLayout *room);



#endif