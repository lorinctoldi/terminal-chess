#include "create.h"

// create a new game from scratch
GameStruct create(void)
{
    system("cls||clear");
    // clear the buffer
    clearBuffer();

    // define new game
    GameStruct match = {0};

    // ask for the information of both players
    printf("Feher jatekos neve: ");
    scanf("%[^\n]", match.white);

    clearBuffer();
    printf("Fekete jatekos neve: ");
    scanf("%[^\n]", match.black);

    // from the start both sides CAN castle
    match.whiteCastle = true;
    match.blackCastle = true;

    // the moves are not yet initalized
    match.moves = NULL;

    // return the match
    return match;
}