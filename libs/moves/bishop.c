#include "moves.h"

// check for valid bishop move
int validBishopMove(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side)
{
  // define the destination square
  char destination = board[destinationFile][destinationRank];

  // check for move style
  if (abs(sourceFile - destinationFile) != abs(sourceRank - destinationRank))
    return 41;

  // check if therfe are pieces in the bishop's path
  int fileIncrement = (destinationFile > sourceFile) ? 1 : -1;
  int rankIncrement = (destinationRank > sourceRank) ? 1 : -1;

  int file = sourceFile + fileIncrement;
  int rank = sourceRank + rankIncrement;

  while (file != destinationFile && rank != destinationRank)
  {
    if (board[file][rank] != ' ')
      return 42;
    file += fileIncrement;
    rank += rankIncrement;
  }

  // check whether the target if your own peace
  char opponentPieces[] = {'p', 'r', 'n', 'q', 'k', 'b'};
  char targetPiece = destination;

  for (int i = 0; i < 6; i++)
        if (targetPiece == (side == 'b' ? opponentPieces[i] : toupper(opponentPieces[i])))
      return 5;

  // if there are no early returns, return 0 (0 -> valid move)
  return 0;
}