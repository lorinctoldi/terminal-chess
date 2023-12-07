#ifndef CHECK_H
#define CHECK_H

#include "valid.h"
#include "./errors.h"
#include "./board.h"

#include <stdlib.h>

#include "../structs/game_struct.h"

#include "../debugmalloc.h"

int checkMove(char **board, int current, char side, GameStruct *match);

#endif