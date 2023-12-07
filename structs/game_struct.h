#ifndef GAME_STRUCT_H
#define GAME_STRUCT_H

#include <stdbool.h>

typedef struct ChessMove
{
  char source[3];         // starting position on board   "(a-h)(1-8)\0"
  char destination[3];    // ending position on board     "(a-h)(1-8)\0"
} ChessMove;

typedef struct GameStruct
{
  ChessMove *moves;       // list of moves
  char white[256];        // white player's name
  char black[256];        // black player's name
  int numMoves;           // black player's name
  int next;               // next player to step (0-w, 1-b)
  bool whiteCastle;       // white ability to castle
  bool blackCastle;       // black ability to castle
} GameStruct;

#endif