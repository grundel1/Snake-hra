#include "snake.h"
#include "ovocie.h"
#include "plocha.h"
#include <ncurses.h>
#include <time.h>

#define RIADKY 30
#define STLPCE 30
#define POCET_OVOCIA 256

typedef struct Hra{
  Snake snake;
  Ovocie ovocie[POCET_OVOCIA];
  char plocha[RIADKY * STLPCE];
  int stavHry;
  time_t cas;
  int limit;
  int mod;
  int riadky;
  int stlpce;
  int pocet_ovocia;
}Hra;

void vytvor_hru(Hra* hra, int riadky, int stlpce, int pocetOvocia, int mod);
void updatni_hru(Hra* hra, int x, int y);
void vykresli_hru(Hra* hra);
