#include "errors.h"

// define the error codes for easier development and debugging
// they are ONLY used in this file
enum ErrorCode
{
  WRONG_SIDE = 1,
  NO_MOVE = 2,
  OUT_OF_BOARD = 3,
  SELECTED_EMPTY = 4,
  FRIENDLY_FIRE = 5,
  CHECK_ALREADY = 6,
  CHECK_THEN = 7,
  CASTLE = 8,
  CASTLE_CHECK = 9,

  PAWN_MOVE = 11,
  PAWN_START = 12,
  PAWN_BLOCKED= 13,
  PAWN_LEFT = 14,
  PAWN_EMPTY = 15,
  PAWN_E = 16,
  PAWN_BACKWARDS = 17,

  KING_MOVE = 21,
  KING_N_KING = 22,

  NIGHT_MOVE = 31,

  BISHOP_MOVE = 41,
  BISHOP_BLOCKED = 42,

  ROOK_MOVE = 51,
  ROOK_BLOCKED = 52,

  QUEEN_MOVE = 91,
  QUEEN_BLOCKED = 92,

  KING_ON_TOP = 101
};

// print error by code and wait 3 sec
int error(int error_code)
{
  switch (error_code)
  {
  case WRONG_SIDE:
    printf("Hiba! Nem a sajat babuddal probaltal lepni!");
    break;
  case NO_MOVE:
    printf("Hiba! Nem leptel!");
    break;
  case SELECTED_EMPTY:
    printf("Hiba! A valasztott mezo ures!");
    break;
  case OUT_OF_BOARD:
    printf("Hiba! Nincs ilyen mezo a tablan!");
    break;
  case FRIENDLY_FIRE:
    printf("Hiba! A sajat babudat probaltad levenni!");
    break;
  case CHECK_ALREADY:
    printf("Hiba! A kiralyod sakkban van!");
    break;
  case CHECK_THEN:
    printf("Hiba! A lepes utan a kiralyod sakkba kerulne!");
    break;
  case CASTLE:
    printf("Hiba! A rosalas nem vegrehajthato!");
    break;
  case CASTLE_CHECK:
    printf("Hiba! A sakkbol nem lehet rosalassal kilepni!");
    break;
  case PAWN_MOVE:
    printf("Hiba! A gyalog oldalra legfeljebb egyet lephet (utes kozben)!");
    break;
  case PAWN_START:
    printf("Hiba! A gyalog kezdohelyzetben legfeljebb ket mezot lephet elore!");
    break;
  case PAWN_LEFT:
    printf("Hiba! A gyalog csak kezdohelyzetben lephet ket mezot!");
    break;
  case PAWN_EMPTY:
    printf("Hiba! Az utest nem lehet vegrehajtani, mert a valasztott mezo ures!");
    break;
  case PAWN_BLOCKED:
    printf("Hiba! Babu a gyalog utjaban!");
    break;
  case PAWN_E:
    printf("Hiba! Ez igy nem jo!");
    break;
  case PAWN_BACKWARDS:
    printf("Hiba! A gyalog nem lephet visszafele!");
    break;
  case NIGHT_MOVE:
    printf("Hiba! A lo csak L alakban lephet!");
    break;
  case BISHOP_MOVE:
    printf("Hiba! A futo csak atlosan mozoghat!");
    break;
  case BISHOP_BLOCKED:
    printf("Hiba! Babu a futo utjaban!");
    break;
  case ROOK_MOVE:
    printf("Hiba! A bastya csak egyenesen mozoghat!");
    break;
  case ROOK_BLOCKED:
    printf("Hiba! Babu a bastya utjaban!");
    break;
  case QUEEN_MOVE:
    printf("Hiba! A vezer csak egyenesen es atlosan mozoghat!");
    break;
  case QUEEN_BLOCKED:
    printf("Hiba! Babu a vezer utjaban!");
    break;
  case KING_MOVE:
    printf("Hiba! A kiraly csak egyenesen es atlosan mozoghat (egy mezot)!");
    break;
  case KING_N_KING:
    printf("Hiba! Ket kiraly nem allhat egymas mellet!");
    break;
  case KING_ON_TOP:
    printf("Hiba! A kiralyt nem lehet leutni!");
    break;
  default:
    printf("Unknown error");
    break;
  }

  printf("\nUjraprobalkozas...\n");
  sleep(3);
  return 1;
}