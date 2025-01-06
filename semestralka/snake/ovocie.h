#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Ovocie {
  int x;
  int y;
  bool zjedene;
} Ovocie;

Ovocie* vytvor_ovocie();
void zrus_ovocie(Ovocie* ovocie);
