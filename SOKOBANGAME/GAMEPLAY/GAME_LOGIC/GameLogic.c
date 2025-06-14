#include "GameLogic.h"
#include "../ARENA_LOGIC/Level.h"
#include "ButtonGame.h"

/*****************************************************/
/* -->           MOVEMENT OBJECT IN GAME         <-- */
/*****************************************************/


//===========================================================//
//== Method untuk melakukan pemeriksaan sata akan bergerak ==//
//===========================================================//
/* {Sopian} */
Boolean move_player (RoomLayout *room, int dx, int dy, const char **map) {
    int new_x = room->player.x + dx;
    int new_y = room->player.y + dy;

    int i,j;
    int box_new_x, box_new_y;

    //memeriksa box atau obstacle di lokasi tujuan
    for (i = 0 ; i < room->box_count ; i++) {
        if (room->boxes[i].x == new_x && room->boxes[i].y == new_y) {

            //menyimpan posisi box jika didorong
            box_new_x = new_x + dx;
            box_new_y = new_y + dy;

            if (map[box_new_y][box_new_x] == '#' || 
                map[box_new_y][box_new_x] == '\0' ) return false;

            //memastikan tidak menabrak box lain
            for ( j = 0 ; j < room->box_count ; j++) {
                if (room->boxes[j].x == box_new_x && 
                    room->boxes[j].y == box_new_y) return false;
            }

            //gerakan box
            room->boxes[i].x = box_new_x;
            room->boxes[i].y = box_new_y;

            //pindahkan posisi player
            room->player.x = new_x;
            room->player.y = new_y;
            return true;
        }
    }
    //kalau tidak menabrak obstakel apapun
    if (map[new_y][new_x] != '#') {
        room->player.x = new_x;
        room->player.y = new_y;

        return true;
    }

    return false;
}


/***************************************************/
/* -->     STATUS MANAGER OBJECT IN GAME       <-- */
/***************************************************/

//=============================================================//
//== Method untuk memeriksa apakah box sudah diposisi target ==//
//=============================================================//
/* {Sopian} */

void update_box_activation_status(RoomLayout *room) {
    for (int i = 0; i < room->box_count; i++) {
        room->boxes[i].is_activated = false;  // Reset dulu status

        for (int j = 0; j < room->target_count; j++) {
            if (room->boxes[i].x == room->targets[j].x &&
                room->boxes[i].y == room->targets[j].y) {
                room->boxes[i].is_activated = true;
                break; // Langsung keluar loop target kalau cocok
            }
        }
    }
}


//===============================================================//
//== Method untuk memeriksa apakah finsih sudah diposisi aktif ==//
//===============================================================//
/* {Sopian} */

void update_finish_activation_status(RoomLayout *room) {
    for (int i = 0; i < room->box_count; i++) {
        room->finish.is_activated = false;  // dipindahin ke start_level

        for (int j = 0; j < room->target_count; j++) {
            if (room->boxes[i].is_activated == false) {
                return;
            }
        }

        room->finish.is_activated = true;
    }
}

/******************************************************/
/* -->       ARENA STATUS - LOGIC IN GAME         <-- */
/******************************************************/

//==========================================================================//
//== Method untuk memeriksa apakah parent finished, dan membuka child nya ==//
//==========================================================================//
/* {Sopian} */
void unlock_child_if_parent_finished (Ptree root) {
    if (!root || root->Type != TYPE_LEVELDATA) return;

    LevelData *level = (LevelData *) root->data;

    if (level->is_finished) {
        Ptree child = root->fs;
        while (child != NULL) {
            LevelData *child_level = (LevelData*) child->data;
            if (!child_level->is_unlocked) {
                child_level->is_unlocked = true;
            }
            child = child->nb;
        }
    }
}

//==========================================================================//
//== Method untuk memeriksa apakah parent finished, dan membuka child nya ==//
//==========================================================================//
/* {Sopian} */




/*****************************************************/
/* -->       ACTION BUTTON LOGIC IN GAME         <-- */
/*****************************************************/

//=====================//
//==>  RESET LOGIC  <==//
//=====================//
/* {Sopian} */

void reset_game(RoomLayout *room, const char **map) {
    pthread_t gameResetSound;
    pthread_create(&gameResetSound, NULL, playGameResetSound, NULL);
    pthread_join(gameResetSound, NULL);
    parse_room(room, map);
}


/***********************************************/
/* -->           BOOLEAN VALIDATOR         <-- */
/***********************************************/

//==================================================//
//== Method untuk memeriksa apakah level complete ==//
//==================================================//
/* {Sopian} */

Boolean is_level_completed(RoomLayout *room) {
    for (int i = 0; i < room->box_count; i++) {
        if (!room->boxes[i].is_activated) {
            return false;
        }
    }
    return true;
}


//===========================================================//
//== Method untuk memeriksa apakah player berada di Finish ==//
//===========================================================//
/* {Sopian} */
Boolean is_player_at_finish (RoomLayout *room) {
    return (room->player.x == room->finish.x &&
            room->player.y == room->finish.y);
}

//=======================================================//
//== Method untuk memeriksa apakah Level Terselesaikan ==//
//=======================================================//
/* {Sopian} */
Boolean is_victory (RoomLayout *room) {
    if (room->finish.is_activated == true) {
        if (!is_player_at_finish(room)) return false;
        return true;
    }
}