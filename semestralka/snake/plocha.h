#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Plocha {
  int vyska;
  int sirka;
  char** svet;
} Plocha;

Plocha* vytvor_plochu();
bool nacitaj_plochu_subor(Plocha* plocha, const char* subor);
void vykresli_plochu(Plocha* plocha);
void zrus_plochu(Plocha* plocha);
