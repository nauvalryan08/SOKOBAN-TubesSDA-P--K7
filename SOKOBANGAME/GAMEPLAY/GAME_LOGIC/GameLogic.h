#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "../ARENA_LOGIC/RoomFactory.h"

//Pointer untuk memanggil void init parsing level
typedef void (*InitLevel)(RoomLayout*);

//===========================================================//
//== Method untuk melakukan pemeriksaan sata akan bergerak ==//
//===========================================================//
/* {Sopian} */
void move_player (RoomLayout *room, int dx, int dy, const char **map);


//=============================================================//
//== Method untuk memeriksa apakah box sudah diposisi target ==//
//=============================================================//
/* {Sopian} */
void update_box_activation_status(RoomLayout *room);


//===============================================================//
//== Method untuk memeriksa apakah finsih sudah diposisi aktif ==//
//===============================================================//
/* {Sopian} */
void update_finish_activation_status(RoomLayout *room);


//==================================================//
//== Method untuk memeriksa apakah level complete ==//
//==================================================//
/* {Sopian} */
boolean is_level_completed(RoomLayout *room);


//===========================================================//
//== Method untuk memeriksa apakah player berada di Finish ==//
//===========================================================//
/* {Sopian} */
boolean is_player_at_finish (RoomLayout *room);


//=======================================================//
//== Method untuk memeriksa apakah Level Terselesaikan ==//
//=======================================================//
/* {Sopian} */
boolean is_victory (RoomLayout *room);


#endif