#include "create.h"

// create a new game from scratch
GameStruct create(void)
{
    //system("clear"); 
    printf("\e[2J\e[H");
    // clear the buffer
    fflush(stdin);

    // define new game
    GameStruct match = {0};

    // ask for the information of both players
    printf("Feher jatekos neve: ");
    scanf("%[^\n]", match.white);

    printf("Feher jatekos Elo pontszama: ");
    scanf("%d%*c", &match.whiteElo);

    printf("Fekete jatekos neve: ");
    scanf("%[^\n]", match.black);

    printf("Fekete jatekos Elo pontszama: ");
    scanf("%d%*c", &match.blackElo);

    // from the start both sides CAN castle
    match.whiteCastle = true;
    match.blackCastle = true;

    // the moves are not yet initalized
    match.moves = NULL;

    // return the match
    return match;
}