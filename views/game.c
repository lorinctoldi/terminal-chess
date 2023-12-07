#include "game.h"

// game function (the top layer with user connection regarding the game)
int game(int isLoad)
{
  // create new board from scratch
  char **board = createBoard();
  // create new match from scratch
  GameStruct match;

  // define input for user input
  int input = 0;
  // define res for game end handling
  // f.e. res = 2 -> dontetlen 
  int res = 0;

  // assign loadad game or newly created game to match
  match = isLoad ? load() : create();
  // make the moves (from match) on the board and handle errors in the process
  for (int i = 0; i < match.numMoves; i++)
  {
    switch (checkMove(board, i, i % 2 == 0 ? 'w' : 'b', &match))
    {
    case 2:
      input = -1;
      res = 3;
      break;
    case 3:
      input = -1;
      res = 4;
      break;
    }
  }

  // store whether the given party offered draw
  bool whiteDraw = false, blackDraw = false;
  // t is used for user input when player steps back. (t -> time)
  int t = 0;

  while(input != -1)
  {
    system("clear || cls");
    // dispay the board
    displayBoard(board);

    // list options
    printf("%s kovetkezik.\n[1] Lepes\n[2] Feladas\n", match.next % 2 == 0 ? "Feher" : "Fekete");
    // dontetlen felajanlasa | dontetlen visszavonasa | dontetlen elfogadasa
    printf("[3] %s\n", (match.next % 2 == 0) ? ((!whiteDraw) ? (blackDraw ? "Dontetlen elfogadasa" : "Dontetlen ajanlasa") : "Dontetlen visszavonasa") : ((!blackDraw) ? (whiteDraw ? "Dontetlen elfogadasa" : "Dontetlen ajanlasa") : "Dontetlen visszavonasa"));
    printf("[4] Visszajatszas\n[5] Mentes\n[6] Kilepes\n\nValasztasa: ");

    // read in user input
    if (scanf("%d", &input) != 1)
    {
      // if the input is not a number clear input buffer and start the loop again
      clearBuffer();
      input = 0;
      continue;
    }

    // define new move for reading in user input
    ChessMove n;

    // handle the input (right format)
    switch (input)
    {
      // make mvoe
    case 1:
      // ask for starting and end position and store them in the "n" move
      printf("Honnan: ");
      scanf(" %[^\n]", n.source);
      printf("Hova: ");
      scanf(" %[^\n]", n.destination);

      // store the move in the list of existing moves
      // if the move is invalid the next move will be saved on it
      match.moves = saveMove(match.moves, match.numMoves, n);

      // check whether the move is valid and handle it
      switch (checkMove(board, match.numMoves, match.next % 2 == 0 ? 'w' : 'b', &match))
      {
        // move is valid
      case 0:
        match.numMoves++;
        match.next++;
        break;
        // stalemate
      case 2:
        input = -1;
        res = 3;
        match.numMoves++;
        break;
        // mate
      case 3:
        input = -1;
        res = 4;
        match.numMoves++;
        break;
        // incorrect, try again
      default:
        break;
      }
      break;
      // resignation
    case 2:
      input = -1;
      res = 1;
      break;
      // draw
    case 3:
      if (match.next % 2 == 0 ? blackDraw : whiteDraw)
      {
        input = -1;
        res = 2;
        break;
      }
      printf("%s", (match.next % 2 == 0 ? whiteDraw : blackDraw) ? "Dontetlen visszavonva.\n" : "Dontetlen felajanlva.\n");
      match.next % 2 == 0 ? (whiteDraw = !whiteDraw) : (blackDraw = !blackDraw);
      break;
      // take step(s) back
    case 4:
      // read in user input
      printf("(legutobbi: %d, legkorabbi: 0)\nVisszajatszas eddig a lepesig: ", match.numMoves);
      scanf("%d", &t);

      // check for range
      if (t > match.numMoves || t < 0)
      {
        printf("%s %d.\n", t < 0 ? "Legkorabbi lepes szama 0." : "Legkesobbi lepes szama", match.numMoves);
        sleep(2);
        break;
      }
      
      // free the existing board
      freeBoard(&board);
      // create new board
      board = createBoard();
      // restore the castleing options for both partys
      match.whiteCastle = true;
      match.blackCastle = true;

      // make moves on the new board from start to user input
      // (t, only used here but have to declare outside of switch case)
      for (int i = 0; i < t; i++)
        checkMove(board, i, i % 2 == 0 ? 'w' : 'b', &match);
      
      // set the next player to t and the numMoves to t
      match.next = t;
      match.numMoves = t;
      break;
      // save game
    case 5:
      // while saving is incorrect:
      // offer the option to save again or quit saving to user
      // if there is no error the save function will print the success message
      while (save(match) == 1)
      {
        printf("Sikertelen mentes.\n[0] Kilepes\n[1] Ujraproblakozas\n");
        scanf("%d", &input);
        if (input != 1)
        {
          input = 0;
          break;
        }
      }
      break;
      // quit
    case 6:
      // free the board and the list of moves
      // then terminate
      freeBoard(&board);
      if (match.moves != NULL)
        free(match.moves);
      return 0;
    default:
      // if the input is not in the list of options:
      // set the input to its base value and start again after 3sec
      printf("Kerlek valassz a listabol!\n");
      input = 0;
      sleep(3);
      break;
    }
  }

  system("clear || cls");

  // display the board then free it
  displayBoard(board);
  freeBoard(&board);
  printf("- - - - - - - - - - - - - - - - - - - - - -\n");

  // print the result of the game (res, only used here)
  if (res == 1)
    printf("%s feladta, %s nyert!\n", match.next % 2 == 0 ? "Feher" : "Fekete", match.next % 2 == 0 ? "fekete" : "feher");
  else if (res == 2)
    printf("Az eredmeny dontetlen.\n");
  else if (res == 3)
    printf("Matt, %s nyert!\n", match.next % 2 == 0 ? "feher" : "fekete");
  else if (res == 4)
    printf("Patt!\n");
  else
  {
    // only free match here if the user quit
    if (match.moves != NULL)
      free(match.moves);
    return 0;
  }

  // offer the user to save the game or quit and read the input
  // after successfull saving the game will quit automatically
  printf("[1] Jatek mentese\n[2] Kilepes\n\nValasztasa: ");
  scanf("%d", &input);

  // while the user wants to save and there is an error
  while (input == 1 && save(match) == 1)
  {
    // offer the option to save or quit
    printf("Sikertelen mentes.\n[1] Ujraproblakozas\n[2] Kilepes\n");
    scanf("%d", &input);
    if (input != 1)
      break;
  }

  // if there are moves, free them
  if (match.moves != NULL)
    free(match.moves);

  // return 0
  return 0;
}