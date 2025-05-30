#ifndef ROOMFACTORY_H
#define ROOMFACTORY_H

#include "../include/boolean.h"
#include "../include/curses.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_OBJECTS 15

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

void parse_room(const char **map, RoomLayout *room);

void print_room(const char **map, const RoomLayout *room);


#endif