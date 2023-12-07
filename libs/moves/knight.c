#include "moves.h"

// check for valid knight move
int validKnightMove(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side)
{
  int rankDifference = abs(destinationRank - sourceRank);
  int fileDifference = abs(destinationFile - sourceFile);

  // check for move style (not L shaped -> invalid)
  if (!((rankDifference == 2 && fileDifference == 1) || (rankDifference == 1 && fileDifference == 2)))
    return 31;

  // define the destination square
  char destination = board[destinationFile][destinationRank];

  // check whether the target if your own peace
  char opponentPieces[] = {'p', 'r', 'n', 'q', 'k', 'b'};

  for (int i = 0; i < 6; i++) {
    if (destination == (side == 'b' ? opponentPieces[i] : toupper(opponentPieces[i])))
      return 5;

  }

  // if there are no early returns, return 0 (0 -> valid move)
  return 0;
}
