#include "valid.h"

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