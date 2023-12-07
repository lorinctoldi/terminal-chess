#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "../debugmalloc.h"

#include "../structs/game_struct.h"
#include "../libs/clear.h"
#include "../libs/create.h"
#include "../libs/board.h"
#include "../libs/load.h"
#include "../libs/save.h"
#include "../libs/check.h"
#include "../libs/move.h"

int game(int isLoad);

#endif