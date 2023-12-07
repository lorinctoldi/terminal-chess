#include "moves.h"

// check whether the given king is in check
int isKingInCheck(char **board, char side)
{
  // get square of given king (loop through board and find the "side"'s king)
  int kingFile, kingRank;

  for (int file = 0; file < 8; file++)
  {
    for (int rank = 0; rank < 8; rank++)
    {
      if (board[file][rank] == (side == 'b' ? 'k' : 'K'))
      {
        kingFile = file;
        kingRank = rank;
        break;
      }
    }
  }

  // check for pawn attack
  if (
      board[kingFile + (side == 'b' ? 1 : -1)][kingRank - 1] == (side == 'b' ? 'P' : 'p') ||
      board[kingFile + (side == 'b' ? 1 : -1)][kingRank + 1] == (side == 'b' ? 'P' : 'p'))
    return 1;

  // check for night attack
  int knightMoves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

  for (int move = 0; move < 8; move++)
  {
    int ni = kingFile + knightMoves[move][0];
    int nj = kingRank + knightMoves[move][1];

    if (!(ni >= 0 && ni < 8 && nj >= 0 && nj < 8)) continue;
    
    if (board[ni][nj] == (side == 'b' ? 'N' : 'n'))
    {
      return 1;
    }
  }

  // check for bishop attack
  int bishopMoves[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

  for (int move = 0; move < 4; move++)
  {
    int ni = kingFile;
    int nj = kingRank;

    while (true)
    {
      ni += bishopMoves[move][0];
      nj += bishopMoves[move][1];

      if (ni >= 0 && ni < 8 && nj >= 0 && nj < 8)
      {
        if (board[ni][nj] == (side == 'b' ? 'B' : 'b') || board[ni][nj] == (side == 'b' ? 'Q' : 'q'))
          return 1;

        if (board[ni][nj] != ' ')
          break;
      }
      else
        break;
    }
  }

  // check for rook attack
  int rookMoves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  for (int move = 0; move < 4; move++)
  {
    int ni = kingFile;
    int nj = kingRank;

    while (true)
    {
      ni += rookMoves[move][0];
      nj += rookMoves[move][1];

      if (ni >= 0 && ni < 8 && nj >= 0 && nj < 8)
      {
        if (board[ni][nj] == (side == 'b' ? 'R' : 'r') || board[ni][nj] == (side == 'b' ? 'Q' : 'q'))
          return 1;

        if (board[ni][nj] != ' ')
          break;
      }
      else
        break;
    }
  }

  // if there is no early return (check), then return 0 (0 -> the given side's king is not in check)
  return 0;
}

// "alternate" creates an alternative board
// on the alternative board it makes the move
// checks whether the king would be in check after the move
int alternate(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side)
{
  // create alternative board
  char **tempBoard = (char **)malloc(8 * sizeof(char *));
  for (int i = 0; i < 8; i++)
  {
    tempBoard[i] = (char *)malloc(8 * sizeof(char));
  }

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      tempBoard[i][j] = board[i][j];
    }
  }

  // make the move on the alternative board
  tempBoard[destinationFile][destinationRank] = tempBoard[sourceFile][sourceRank];
  tempBoard[sourceFile][sourceRank] = ' ';

  // result definition is needed, if I return it immidiately I can not free the alternative board
  int result = isKingInCheck(tempBoard, side);

  // free the temporary board
  for (int i = 0; i < 8; i++)
  {
    free(tempBoard[i]);
  }
  free(tempBoard);

  // return the result (whether the king is in check after the move)
  return result;
}

// in chess, 2 kings can NOT stand on neighbouring squares
int kingAdjacent(char **board, int destinationFile, int destinationRank, char side)
{
  // define opponent's king
  char king = side == 'b' ? 'K' : 'k';

  // check for opponent's king near the destination square
  // if found, return 1 (there is a king there)
  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++)
      if (destinationFile + i >= 0 && destinationFile + i < 8 &&
          destinationRank + j >= 0 && destinationRank + j < 8 &&
          board[destinationFile + i][destinationRank + j] == king)
        return 1;

  // if there is no early return, return 0 (0 -> move is valid)
  return 0;
}

// check for valid king move
int validKingMove(char **board, int sourceFile, int sourceRank, int destinationFile, int destinationRank, char side, bool castle)
{
  // check for castle
  if(castle && sourceFile == destinationFile && (sourceRank == 4 && (destinationRank == 2 || destinationRank == 6))) {
    // king can not castle while in check
    if(isKingInCheck(board, side)) {
      return 9;
    }

    // check for pieces in castle's path, if there is a piece the move is invalid
    // check whether while doing the castle, would the king be in check on any of the affected squares
    int file = side == 'b' ? 0 : 7;
    int from = destinationRank > sourceRank ? sourceRank : destinationRank;
    from++;
    int to = destinationRank < sourceRank ? sourceRank : destinationRank;
    for(; from < to; from++) {
      if(board[file][from] != ' ') {
        return 8;
      }
      if(alternate(board, sourceFile, sourceRank, destinationFile, from, side)) {
        return 8;
      }
    }

    // do the caste move!
    if(destinationRank == 2) {
      if(board[file][0] != (side == 'b' ? 'r' : 'R')) return 8;
      board[file][0] = ' ';
      board[file][3] = (side == 'b' ? 'r' : 'R');
    } else {
      if(board[file][7] != (side == 'b' ? 'r' : 'R')) return 8;
      board[file][7] = ' ';
      board[file][5] = (side == 'b' ? 'r' : 'R');
    }

    // return valid move if there are no errors
    return 0;
  }

  // check whether the king stepped ONLY one square (castle case is handled prior)
  if (abs(destinationRank - sourceRank) > 1 || abs(destinationFile - sourceFile) > 1)
    return 21;

  // check whether there is a neighbouring king on the destination square
  if (kingAdjacent(board, destinationFile, destinationRank, side))
    return 22;

  // check whether we hit our own piece
  char destination = board[destinationFile][destinationRank];
  char opponentPieces[] = {'p', 'r', 'n', 'q', 'k', 'b'};
  char targetPiece = destination;

  for (int i = 0; i < 6; i++)
    if (targetPiece == (side == 'b' ? opponentPieces[i] : toupper(opponentPieces[i])))
      return 5;

  // if there are no early returns, return 0 (0 -> valid move)
  return 0;
}
