#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Hra{
  int sirkaSveta;
  int vyskaSveta;
  char** svet;
  int skore;
  int stav;
}Hra;

Hra* vytvor_hru();
void spusti_hru(Hra* hra);
void zrus_hru(Hra* hra);
