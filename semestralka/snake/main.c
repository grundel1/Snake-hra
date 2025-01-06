#include <stdio.h>
#include "hra.h"
#include "plocha.h"
#include "snake.h"
#include "ovocie.h"
#include <ncurses.h>

#define pocet_riadkov 10
#define pocet_stlpcov 10

int main(int argc, char *argv[])
{ 
  Hra* hra = vytvor_hru();
  Plocha* plocha = vytvor_plochu();
  Snake* snake = vytvor_hada();
  Ovocie* ovocie = vytvor_ovocie();

  if (hra == NULL) {
    printf("Nepodarilo sa vytvorit hru\n");
    return -1;
  }

  if (!nacitaj_plochu_subor(plocha, "../../snake/svet.txt")) {
    fprintf(stderr, "Nepodarilo sa nacitat plochu zo suboru!\n");
    zrus_plochu(plocha);
    zrus_hru(hra);
    return -1;
  }

  vykresli_plochu(plocha);

  //spustiHru(hra);

  zrus_ovocie(ovocie);
  zrus_hada(snake);
  zrus_plochu(plocha);
  zrus_hru(hra);

  return 0;
}
