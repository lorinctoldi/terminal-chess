#include "moves.h"
#include "../../debugmalloc.h"

// define min
int min(int a, int b)
{
  return a < b ? a : b;
}

// define max
int max(int a, int b)
{
  return a > b ? a : b;
}

// check for valid rook move
int validRookMove(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side)
{
  // check for move style (not ONLY vertical || not ONLY horizontal -> invalid move)
  if (destinationFile != sourceFile && destinationRank != sourceRank)
    return 51;

  // check for pieces in rook's path horizontally
  for (int x = min(destinationRank, sourceRank) + 1; x < max(destinationRank, sourceRank); x++)
    if (board[destinationFile][x] != ' ')
      return 52;

  // check for pieces in rook's path vertically
  for (int y = min(destinationFile, sourceFile) + 1; y < max(destinationFile, sourceFile); y++)
    if (board[y][destinationRank] != ' ')
      return 52;

  // check whether the target if your own peace
  char destination = board[destinationFile][destinationRank];
  char opponentPieces[] = {'p', 'r', 'n', 'q', 'k', 'b'};
  char targetPiece = destination;

  for (int i = 0; i < 6; i++)
    if (targetPiece == (side == 'b' ? opponentPieces[i] : toupper(opponentPieces[i])))
      return 5;

  // if there are no early returns, return 0 (0 -> valid move)
  return 0;
}
