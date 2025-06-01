#ifndef LEVELSCREEN_H
#define LOBBYSCREEN_H

#define maxbtn_area 50

#include "../GAMEPLAY/ARENA_LOGIC/Level.h"
#include "../GAMEPLAY/GAME_LOGIC/GameStart.h"
#include "../UTILS/include/curses.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void print_lvl(RoomLayout *room);
void acs_converter(char **asciiart);

#endif // !LEVELSCREEN_H
