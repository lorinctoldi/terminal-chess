#ifndef VALID_H
#define VALID_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "board.h"
#include "../debugmalloc.h"

// gyalog
int validPawnMove(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side);

// futó
int validBishopMove(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side);

// ló
int validKnightMove(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side);

// bástya
int validRookMove(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side);

// királynő
int validQueenMove(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side);

// király
int isKingInCheck(char **board, char side);
int alternate(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side);
int kingAdjacent(char **board, int destinationFile, int destinationRank, char side);
int validKingMove(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side, bool castle);

#endif