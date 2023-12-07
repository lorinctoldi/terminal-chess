#include "board.h"

#ifdef _WIN32
#include <windows.h>
#endif

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
      {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};

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
  #ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  #endif

  for (int i = 0; i < 8; i++)
  {
    printf("%d | ", 8 - i);
    for (int j = 0; j < 8; j++)
    {
      switch (board[i][j])
      {
      case 'R':
        printf("♜ ");
        break;
      case 'N':
        printf("♞ ");
        break;
      case 'B':
        printf("♝ ");
        break;
      case 'Q':
        printf("♛ ");
        break;
      case 'K':
        printf("♚ ");
        break;
      case 'P':
        printf("♟ ");
        break;
      case 'r':
        printf("♖ ");
        break;
      case 'n':
        printf("♘ ");
        break;
      case 'b':
        printf("♗ ");
        break;
      case 'q':
        printf("♕ ");
        break;
      case 'k':
        printf("♔ ");
        break;
      case 'p':
        printf("♙ ");
        break;
      case ' ':
        printf("  ");
        break;
      default:
        printf("%c ", board[i][j]);
      }
    }
    printf("\n");
  }
  printf("    ---------------\n    a b c d e f g h\n\n");
}