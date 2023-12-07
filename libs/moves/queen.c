#include "moves.h"

// check for valid queen move
int validQueenMove(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side)
{
  // check for move style (not diagonal && not vertical && not horizontal -> invalid move)
  if (sourceRank != destinationRank && sourceFile != destinationFile &&
      abs(destinationRank - sourceRank) != abs(destinationFile - sourceFile))
    return 91;

  int rankIncrement = (destinationRank > sourceRank) ? 1 : ((destinationRank < sourceRank) ? -1 : 0);
  int fileIncrement = (destinationFile > sourceFile) ? 1 : ((destinationFile < sourceFile) ? -1 : 0);

  // check for pieces in queen's path diagonally
  int rank = sourceRank + rankIncrement;
  int file = sourceFile + fileIncrement;

  while (rank != destinationRank || file != destinationFile)
  {
    if (board[file][rank] != ' ')
      return 92;

    rank += rankIncrement;
    file += fileIncrement;
  }

  // check whether the target is your own peace
  char destination = board[destinationFile][destinationRank];
  char opponentPieces[] = {'p', 'r', 'n', 'q', 'k', 'b'};
  char targetPiece = destination;

  for (int i = 0; i < 6; i++)
    if (targetPiece == (side == 'b' ? opponentPieces[i] : toupper(opponentPieces[i])))
      return 5;

  // if there are no early returns, return 0 (0 -> valid move)
  return 0;
}
