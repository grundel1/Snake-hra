#include "ovocie.h"

void vytvor_ovocie(Ovocie* ovocie, int riadky, int stlpce) {
  ovocie->x = 1 + rand() % (stlpce - 2);
  ovocie->y = 1 + rand() % (riadky - 2);
  ovocie->zjedene = 0;
}

void vykresli_ovocie(Ovocie* ovocie, char* plocha, int stlpce, int pocet) {
  for (int i = 0; i < pocet; i++) {
    if (!ovocie[i].zjedene) {
      plocha[ovocie[i].y * stlpce + ovocie[i].x] = 'o';
    }
  }
}
