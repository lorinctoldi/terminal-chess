#include "save.h"

// save the match in file
int save(GameStruct match)
{
  // read filename from user
  char filename[250];
  printf("File neve: ");
  scanf("%s", filename);

  // create custom data path (storage folder)
  char dataFilePath[256];
  snprintf(dataFilePath, sizeof(dataFilePath), "data/%s", filename);

  // create file in folder
  FILE *file = fopen(dataFilePath, "w");

  // handle errors regarding file
  if (file == NULL)
  {
    perror("Hiba a file megnyitasa soran!\n");
    return 1;
  }

  // write the informations of both players to top of file
  fprintf(file, "[White \"%s\"]\n", match.white);
  fprintf(file, "[Black \"%s\"]\n", match.black);

  // write the moves to the file in the required format (if there are moves)
  for (int i = 0; i < match.numMoves; i++)
  {
    fprintf(file, "%d.%s-%s ", i + 1, match.moves[i].source, match.moves[i].destination);
  }

  // close the file
  fclose(file);
  // print success message and wait 2 sec
  printf("Sikeres mentes\n");
  sleep(2);

  // return 0 (0 -> successfull saving)
  return 0;
}