#include <stdio.h>
#include <stdlib.h>

#define MAX_DLZKA 256

typedef struct Pozicia {
  int x;
  int y;
} Pozicia;

typedef struct Snake {
  int dlzka;
  Pozicia cast[MAX_DLZKA];
} Snake;

Snake* vytvor_hada();
void pohni_hada(Snake* snake, int moveX, int moveY);
void zrus_hada(Snake* snake);
