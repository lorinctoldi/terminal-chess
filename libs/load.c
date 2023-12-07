#include "load.h"

// convert the string token to a valid move
ChessMove parseMove(char *move)
{
    // define new move
    ChessMove chessMove;

    // check for the length of the token
    // we have to start from backwards 
    // otherwise after move 9. it's incorrect 
    // f.e. "10.e2-e4" -> ".e", "-e"
    int l = strlen(move);

    // read in the two moves from the token
    chessMove.source[0] = move[l-5];
    chessMove.source[1] = move[l-4];
    chessMove.source[2] = '\0';

    chessMove.destination[0] = move[l-2];
    chessMove.destination[1] = move[l-1];
    chessMove.destination[2] = '\0';

    // return the move
    return chessMove;
}

// load game from file
GameStruct load(void)
{
    system("clear || cls");
    printf("A fajl a data nevu mappabol valasztodik ki. \nA jatszma betoltesehez adja meg a file nevet es kiterjeszteset (pl. proba.txt): ");

    // read in the file name
    char filename[250];
    scanf("%s", filename);

    // initialize new match
    GameStruct match = {0};

    // create the path of the file (data folder must be added)
    char dataFilePath[256];
    snprintf(dataFilePath, sizeof(dataFilePath), "data/%s", filename);

    // read file from the data folder
    FILE *file = fopen(dataFilePath, "r");

    // handle file error    
    if (file == NULL)
    {
        // if there is an error while reading a file
        // allow the user to load a file again or create a new game from scratch
        printf("\nA fájlt nem sikerült megnyitni.\n[1] Ujraprobalkozas\n[2] Uj jatek kezdese\n");
        int ujra = 0;
        scanf("%d", &ujra);
        return ujra == 1 ? load() : create();
    }

    // initialize a string to store the readed values
    char line[4096];
    while (fgets(line, sizeof(line), file))
    {
        // check for white player's name
        if (strstr(line, "[White \"") != NULL)
            sscanf(line, "[White \"%[^\"]\"]", match.white);
        // check for black player's name
        else if (strstr(line, "[Black \"") != NULL)
            sscanf(line, "[Black \"%[^\"]\"]", match.black);
        // check whether the first character in line is a digit
        else if (isdigit(line[0]))
        {
            // read token till next space "1.e2-e4 2.e7-e5" -> token = "1.e2-e4"
            char *token = strtok(line, " ");
            while (token != NULL)
            {
                // create move from the string token with parseMove() function
                // add the move to the list of moves in the match
                match.moves = saveMove(match.moves, match.numMoves++, parseMove(token));
                match.next++;

                // read in the next token
                token = strtok(NULL, " ");
            }
        }
    }

    // close file
    fclose(file);    

    // both players can castle on starting position
    // it might change after validity check in the game.c when it is used
    match.whiteCastle = true;
    match.blackCastle = true;

    // return the defined match
    return match;
}
