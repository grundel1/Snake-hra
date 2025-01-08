#include "snake.h"
#include "ovocie.h"
#include "plocha.h"
#include <ncurses.h>

#define STLPCE 20
#define RIADKY 20

typedef struct Hra{
  Snake snake;
  Ovocie ovocie[256];
  char plocha[RIADKY * STLPCE];
  int stavHry;
}Hra;

void vytvor_hru(Hra* hra);
void updatni_hru(Hra* hra, int x, int y);
void vykresli_hru(Hra* hra);
