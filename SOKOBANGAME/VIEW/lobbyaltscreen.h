#ifndef ALTLOBBY_H
#define ALTLOBBY_H

#include "viewtoolkit.h"
#include "../../UTILS/include/curses.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int x, y;
  int direction;
} Anim;

void print_alt_title();

#endif