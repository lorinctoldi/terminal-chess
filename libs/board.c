#include "board.h"

// make the starting board
void resetBoard(char ***board)
{
  char initialBoard[8][8] = {
      {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
      {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
      {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
      {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };
  // check for stalemate
  // char initialBoard[8][8] = {
  //     {' ', ' ', ' ', ' ', 'k', ' ', ' ', ' '},
  //     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
  //     {' ', ' ', ' ', 'Q', ' ', 'Q', ' ', ' '},
  //     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
  //     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
  //     {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
  //     {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
  //     {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
  //   };

  // allocate memory for the board
  *board = (char **)malloc(8 * sizeof(char *));
  // fill the board with pieces
  for (int i = 0; i < 8; i++)
  {
    (*board)[i] = (char *)malloc(8 * sizeof(char));
    for (int j = 0; j < 8; j++)
    {
      (*board)[i][j] = initialBoard[i][j];
    }
  }
}

// create a new board
char **createBoard()
{
  char **board;
  resetBoard(&board);
  return board;
}

// free the existing board
void freeBoard(char ***board)
{
  for (int i = 0; i < 8; i++)
  {
    free((*board)[i]);
  }
  free(*board);
  *board = NULL;
}

// display the board
void displayBoard(char **board)
{
  for (int i = 0; i < 8; i++)
  {
    printf("%d | ", 8 - i);
    for (int j = 0; j < 8; j++)
    {
      switch (board[i][j])
      {
      case 'r':
        printf("\u2656 ");  // Black Rook
        break;
    case 'n':
        printf("\u2658 ");  // Black Knight
        break;
    case 'b':
        printf("\u2657 ");  // Black Bishop
        break;
    case 'q':
        printf("\u2655 ");  // Black Queen
        break;
    case 'k':
        printf("\u2654 ");  // Black King
        break;
    case 'p':
        printf("\u2659 ");  // Black Pawn
        break;
    case 'R':
        printf("\u265C ");  // White Rook
        break;
    case 'N':
        printf("\u265E ");  // White Knight
        break;
    case 'B':
        printf("\u265D ");  // White Bishop
        break;
    case 'Q':
        printf("\u265B ");  // White Queen
        break;
    case 'K':
        printf("\u265A ");  // White King
        break;
    case 'P':
        printf("\u265F ");  // White Pawn
        break;
    case ' ':
        printf("  ");  // Empty Square
        break;
      default:
        printf("%c ", board[i][j]);
      }
    }
    printf("\n");
  }
  printf("    ---------------\n    a b c d e f g h\n\n");
}