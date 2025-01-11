#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_DLZKA 256

typedef struct CastHada {
  int x;
  int y;
} CastHada;

typedef struct Snake {
  int dlzka;
  CastHada cast[MAX_DLZKA];
} Snake;

void vytvor_hada(Snake* snake, int x, int y);
void pohni_hada(Snake* snake, int moveX, int moveY, int riadky, int stlpce, int mod);
void vykresli_hada(Snake* snake, char* plocha, int stlpce);
bool zjedz_ovocie(Snake* snake, int ovocieX, int ovocieY);
