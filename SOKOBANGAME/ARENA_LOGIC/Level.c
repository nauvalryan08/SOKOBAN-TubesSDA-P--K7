#include "Level.h"

const char *Level_1c1_map[] = {
    "####################",
    "#     @     $   .  #",
    "#                  #",
    "#           F      #",
    "####################",
    NULL
};

const char *Level_1c2_map[] = {
    "####################",
    "# F            # . #",
    "#   $   #      #   #",
    "#       #   @      #",
    "#                  #",
    "#######    #########",
    "      #    #        ",
    "      ######        ",   
    NULL
};


void Level_1c1 (RoomLayout *room) {
    parse_room(Level_1c1_map, room);
}

void Level_1c2 (RoomLayout *room) {
    parse_room(Level_1c2_map, room);
}