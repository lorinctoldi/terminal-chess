#include "moves.h"

// check for valid pawn move
int validPawnMove(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side)
{
  // check whether the step backwards
  if ((side == 'b' && sourceFile > destinationFile) || (side == 'w' && sourceFile < destinationFile))
    return 17;

  // check whether you move more than 1 horizontally
  if (abs(sourceRank - destinationRank) > 1)
    return 11;

  // check whether your hit move is valid, (horizontal = 1, vertical != 1 -> invalid)
  if (abs(sourceRank - destinationRank) == 1 && abs(sourceFile - destinationFile) != 1)
    return 16;

  // check whether this is the pawn's first move
  bool starting = (side == 'b' && sourceFile == 1) || (side == 'w' && sourceFile == 6);

  if (starting)
  {
    // check whether the first move is more than 2
    if (abs(destinationFile - sourceFile) > 2)
      return 12;

    // check whether the first move is 2
    if (abs(destinationFile - sourceFile) == 2)
    {
      // check for horizontal move (horizontal move -> invalid)
      if (destinationRank != sourceRank)
        return 11;

      // check for pieces in pawn's path
      if (board[destinationFile - (side == 'b' ? 1 : -1)][sourceRank] != ' ' || board[destinationFile][sourceRank] != ' ')
        return 13;
    }
  }
  else
  {
    if (sourceRank == destinationRank)
    {
      // check whether you moved more than 1 (vertical > 1 -> invalid)
      if (abs(destinationFile - sourceFile) > 1)
        return 14;

      // check whether the given square is empty (target != ' ' -> invalid)
      if (board[destinationFile][sourceRank] != ' ')
        return 13;
    }
  }

  // check for hit move
  if (sourceRank != destinationRank)
  {
    // check whether you want to hit your own piece
    char destination = board[destinationFile][destinationRank];
    char opponentPieces[] = {'p', 'r', 'n', 'q', 'k', 'b'};
    char targetPiece = destination;

    for (int i = 0; i < 6; i++)
    {
    if (targetPiece == (side == 'b' ? opponentPieces[i] : toupper(opponentPieces[i])))
        return 5;
    }

    // there is no piece to be hit
    if (destination == ' ')
      return 15;
  }

  // if there are no early returns, return 0 (0 -> valid move)
  return 0;
}