#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "../ARENA_LOGIC/RoomFactory.h"
#include "../../STRUCTURES/stack.h"
#include "../../STRUCTURES/tree.h"


//================================//
//==>  STRUCT OBJECT & LAYOUT  <==//
//================================//
/* {Sopian} */

//Pointer untuk memanggil void init parsing level
typedef void (*InitLevel)(RoomLayout*);


/*****************************************************/
/* -->           MOVEMENT OBJECT IN GAME         <-- */
/*****************************************************/

//===========================================================//
//== Method untuk melakukan pemeriksaan sata akan bergerak ==//
//===========================================================//
/* {Sopian} */
Boolean move_player (RoomLayout *room, int dx, int dy, const char **map); //true jika berpindah



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


//==========================================================================//
//== Method untuk memeriksa apakah parent finished, dan membuak child nya ==//
//==========================================================================//
/* {Sopian} */
void unlock_child_if_parent_finished (Ptree root);


/*****************************************************/
/* -->       ACTION BUTTON LOGIC IN GAME         <-- */
/*****************************************************/

//=====================//
//==>  RESET LOGIC  <==//
//=====================//
/* {Sopian} */
void reset_game(RoomLayout *room, const char **map);


/***********************************************/
/* -->           BOOLEAN VALIDATOR         <-- */
/***********************************************/

//==================================================//
//== Method untuk memeriksa apakah level complete ==//
//==================================================//
/* {Sopian} */
Boolean is_level_completed(RoomLayout *room);


//===========================================================//
//== Method untuk memeriksa apakah player berada di Finish ==//
//===========================================================//
/* {Sopian} */
Boolean is_player_at_finish (RoomLayout *room);


//=======================================================//
//== Method untuk memeriksa apakah Level Terselesaikan ==//
//=======================================================//
/* {Sopian} */
Boolean is_victory (RoomLayout *room);




#endif