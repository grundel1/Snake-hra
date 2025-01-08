#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Ovocie {
  int x;
  int y;
  int zjedene;
} Ovocie;

void vytvor_ovocie(Ovocie* ovocie, int riadky, int stlpce);
void vykresli_ovocie(Ovocie* ovocie, char* plocha, int stlpce, int pocet);
