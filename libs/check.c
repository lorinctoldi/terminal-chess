#include "check.h"

// check whether the move is on the board (a-h, 1-8...)
int isMoveOnBoard(int rank, int file)
{
  return (rank >= 0 && rank < 8 && file >= 0 && file < 8);
}

// check whether the given piece is your own (can't make a move with the opponent's piece)
int checkSide(char selected, char side)
{
  if ((side == 'b' && islower(selected)) || (side == 'w' && isupper(selected)))
    return 0;
  else
    return 1;
}

// check for every legal move that could be left
// used for checking mate (king is ALREADY in check)
// and for check stalemate (king is NOT in check)
int legalMovesLeft(char **board, char side, bool castle)
{
  // to save memory and time we need to shorten the cases
  // we can not step with the opponent's piece or with no piece so we skip those
  char pieces[] = {'p', 'r', 'n', 'q', 'k', 'b'};

  for (int file = 0; file < 8; file++)
  {
    for (int rank = 0; rank < 8; rank++)
    {
      char current = board[file][rank];
      // no piece -> continue
      if (current == ' ')
        continue;

      // check whether the piece is our own, if not -> continue
      bool skipRank = true;
      for (int c = 0; c < 6; c++)
      {
        if (current == (side == 'b' ? pieces[c] : toupper(pieces[c])))
        {
          skipRank = false;
          break;
        }
      }
      if (skipRank)
        continue;


      int delta = (side == 'b' ? 1 : -1);

      // check for pawn's move
      // if any of them is possible return 0, as there are legal moves left
      // the edgecases are neccessary because the pawn can hit, step 2 or 1
      if (tolower(current) == 'p')
      {
        if (!validPawnMove(board, file, rank, file + delta, rank, side) &&
            !alternate(board, file, rank, file + delta, rank, side))
        {
          return 0;
        }

        if (file == (side == 'b' ? 1 : 6) &&
            !validPawnMove(board, file, rank, file + 2 * delta, rank, side) &&
            !alternate(board, file, rank, file + 2 * delta, rank, side))
        {
          return 0;
        }

        if (isMoveOnBoard(file + delta, rank-1) &&
            !validPawnMove(board, file, rank, file + delta, rank - 1, side) &&
            !alternate(board, file, rank, file + delta, rank - 1, side))
        {
          return 0;
        }

        if (isMoveOnBoard(file + delta, rank+1) &&
            !validPawnMove(board, file, rank, file + delta, rank + 1, side) &&
            !alternate(board, file, rank, file + delta, rank + 1, side))
        {
          return 0;
        }
      }
      // check for night's move
      else if (tolower(current) == 'n')
      {
        int knightMoves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

        for (int move = 0; move < 8; move++)
        {
          int ni = file + knightMoves[move][0];
          int nj = rank + knightMoves[move][1];
          
          if(!isMoveOnBoard(nj, ni)) continue;
          if(validKnightMove(board, file, rank, ni, nj, side)) continue;
          if (alternate(board, file, rank, ni, nj, side)) continue;
          
          return 0;
        }
      }
      // check for bishop's move
      else if (tolower(current) == 'b')
      {
        int bishopMoves[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        for (int move = 0; move < 4; move++)
        {
          int ni = file;
          int nj = rank;

          while (true)
          {
            ni += bishopMoves[move][0];
            nj += bishopMoves[move][1];

            if (isMoveOnBoard(nj, ni) &&
                !validBishopMove(board, file, rank, ni, nj, side) &&
                !alternate(board, file, rank, ni, nj, side))
            {
              return 0;
            }

            if (!isMoveOnBoard(nj, ni) || board[ni][nj] != ' ')
              break;
          }
        }
      }
      // check for rook's move
      else if (tolower(current) == 'r')
      {
        int rookMoves[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int move = 0; move < 4; move++)
        {
          int ni = file;
          int nj = rank;

          while (true)
          {
            ni += rookMoves[move][0];
            nj += rookMoves[move][1];

            if (isMoveOnBoard(nj, ni) &&
                !validRookMove(board, file, rank, ni, nj, side) &&
                !alternate(board, file, rank, ni, nj, side))
            {
              return 0;
            }

            if (!isMoveOnBoard(nj, ni) || board[ni][nj] != ' ')
              break;
          }
        }
      }
      // check for queen's move
      else if (tolower(current) == 'q')
      {
        int queenMoves[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        for (int move = 0; move < 8; move++)
        {
          int ni = file;
          int nj = rank;

          while (true)
          {
            ni += queenMoves[move][0];
            nj += queenMoves[move][1];

            if (isMoveOnBoard(nj, ni) &&
                !validQueenMove(board, file, rank, ni, nj, side) &&
                !alternate(board, file, rank, ni, nj, side))
            {
              return 0;
            }

            if (!isMoveOnBoard(nj, ni) || board[ni][nj] != ' ')
              break;
          }
        }
      }
      // check for king's move
      else if (tolower(current) == 'k')
      {
        int kingMoves[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        for (int move = 0; move < 8; move++)
        {
          int ni = file + kingMoves[move][0];
          int nj = rank + kingMoves[move][1];

            int a = isMoveOnBoard(nj, ni);
            if(!a) continue;

            int b = validKingMove(board, file, rank, ni, nj, side, castle);
            if(b) continue;

            int c = alternate(board, file, rank, ni, nj, side);
            if(c) continue;
            
              return 0;
        }
      }
    }
  }

  // if no legal moves are found, return 1 (1 -> no legal moves)
  return 1;
}

// check whether the move is legal (can be made) or not
int checkMove(char **board, int current, char side, GameStruct *match)
{
  // destruct the move to integers so we can navigate on board (array)
  int sourceRank = match->moves[current].source[0] - 'a';
  int sourceFile = 7 - (match->moves[current].source[1] - '1');
  int destinationRank = match->moves[current].destination[0] - 'a';
  int destinationFile = 7 - (match->moves[current].destination[1] - '1');


  // give error if the move is out of board
  if (!isMoveOnBoard(sourceRank, sourceFile) || !isMoveOnBoard(destinationRank, destinationFile)) {
    return error(3);
  }
  
  if(board[destinationFile][destinationRank] == 'k'|| board[destinationFile][destinationRank] == 'K') {
    return error(101);
  }

  // give error if the target square is the same as the starting sqaure
  if (sourceRank == destinationRank && sourceFile == destinationFile)
    return error(1);

  // give error if there is no choosen piece
  if (board[sourceFile][sourceRank] == ' ')
    return error(4);

  // define the selected piece and check if it is on our side
  char selected = board[sourceFile][sourceRank];
  if (checkSide(selected, side) != 0)
    return error(1);

  // check whether our king is in check or would it be after making the move
  // give error's according to these 2 statements
  bool alreadyInCheck = isKingInCheck(board, side) == 1;
  bool wouldBeInCheck = alternate(board, sourceFile, sourceRank, destinationFile, destinationRank, side) == 1;
  if (wouldBeInCheck && alreadyInCheck)
  {
    return error(6);
  }
  if (wouldBeInCheck) {
    return error(7);
  }

  // check for pieces move legality
  switch (selected)
  {
    // rook
  case 'R':
  case 'r':
    if (validRookMove(board, sourceFile, sourceRank, destinationFile, destinationRank, side))
    {
      return error(validRookMove(board, sourceFile, sourceRank, destinationFile, destinationRank, side));
    } else {
     side == 'b' ? (match->blackCastle = false) : (match->whiteCastle = false);
    }
    break;
    // night
  case 'N':
  case 'n':
    if (validKnightMove(board, sourceFile, sourceRank, destinationFile, destinationRank, side))
    {
      return error(validKnightMove(board, sourceFile, sourceRank, destinationFile, destinationRank, side));
    }
    break;
    // pawn
  case 'P':
  case 'p':
    if (validPawnMove(board, sourceFile, sourceRank, destinationFile, destinationRank, side))
    {
      return error(validPawnMove(board, sourceFile, sourceRank, destinationFile, destinationRank, side));
    }
    break;
    // bishop
  case 'B':
  case 'b':
    if (validBishopMove(board, sourceFile, sourceRank, destinationFile, destinationRank, side))
    {
      return error(validBishopMove(board, sourceFile, sourceRank, destinationFile, destinationRank, side));
    }
    break;
    // queen
  case 'Q':
  case 'q':
    if (validQueenMove(board, sourceFile, sourceRank, destinationFile, destinationRank, side))
    {
      return error(validQueenMove(board, sourceFile, sourceRank, destinationFile, destinationRank, side));
    }
    break;
    // king
  case 'K':
  case 'k':
    if (validKingMove(board, sourceFile, sourceRank, destinationFile, destinationRank, side, side == 'b' ? match->blackCastle : match->whiteCastle))
    {
      return error(validKingMove(board, sourceFile, sourceRank, destinationFile, destinationRank, side, side == 'b' ? match->blackCastle : match->whiteCastle));
    } else {
      side == 'b' ? (match->blackCastle = false) : (match->whiteCastle = false);
    }
    break;
  }

  // make the move
  board[destinationFile][destinationRank] = board[sourceFile][sourceRank];
  board[sourceFile][sourceRank] = ' ';
  
  // check whether the opponent is mated or whether it is stalemate
  // if we do not check here then he would have to make a step to find out
  // but that seem unlogical...
  bool opponentInCheck =  isKingInCheck(board, side == 'b' ? 'w' : 'b');
  int legalMoves = legalMovesLeft(board, side == 'b' ? 'w' : 'b', side == 'b' ? match->blackCastle : match->whiteCastle);
  
  // if already in check and no legal moves left it is mate
  // the side that made the move won
  if(opponentInCheck && legalMoves) {
    return 2;
  }

  // if the opponent is not in check but there is no legal moves left it's a stalemate
  if(legalMoves) {
    return 3;
  }

  // return 0 if the move is done and valid (0 -> move done)
  return 0;
}