#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "../ARENA_LOGIC/RoomFactory.h"
#include "../../STRUCTURES/stack.h"

//================================//
//==>  STRUCT OBJECT & LAYOUT  <==//
//================================//
/* {Sopian} */

typedef Stack GameUndo;

//Pointer untuk memanggil void init parsing level
typedef void (*InitLevel)(RoomLayout*);



/*****************************************************/
/* -->           MOVEMENT OBJECT IN GAME         <-- */
/*****************************************************/

//===========================================================//
//== Method untuk melakukan pemeriksaan sata akan bergerak ==//
//===========================================================//
/* {Sopian} */
void move_player (RoomLayout *room, int dx, int dy, const char **map);



/***************************************************/
/* -->     STATUS MANAGER OBJECT IN GAME       <-- */
/***************************************************/

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


/*****************************************************/
/* -->       ACTION BUTTON LOGIC IN GAME         <-- */
/*****************************************************/

//=====================//
//==>  RESET LOGIC  <==//
//=====================//
/* {Sopian} */
void reset_game(RoomLayout *room, InitLevel Level);

//=====================//
//==>  UNDO LOGIC  <==//
//=====================//
/* {Sopian} */
void save_state(GameUndo *prevMove, const RoomLayout *room);

void undo_game(GameUndo *prevMove, RoomLayout *currRoom);


/***********************************************/
/* -->           BOOLEAN VALIDATOR         <-- */
/***********************************************/

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