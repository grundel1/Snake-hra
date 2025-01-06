#include "hra.h"

Hra* vytvor_hru() {
  Hra* novaHra = (Hra*) malloc(sizeof(Hra));
  if (!novaHra) {
    return NULL;
  }
  
  novaHra->vyskaSveta = 0;
  novaHra->sirkaSveta = 0;
  novaHra->svet = NULL;
  novaHra->skore = 0;

  return novaHra;
}

void spusti_hru(Hra* hra) {
  if (hra == NULL) {
    printf("Hra nevznikla\n");
    return;
  }
  int vyber;
  printf("MENU\n");
  printf("Pomocou cisla si zvol co chces spravit.\n");
  printf("1. Nova hra\n2.Koniec hry\n");

  scanf("%d", &vyber);

  if (vyber == 1) {
    printf("Hra zacne odznova\n");
  } else if (vyber == 2) {
    printf("Hra skonci\n");
    return; 
  } else {
    printf("Zle zadany vyber\n");
  }
}
  
void zrus_hru(Hra* hra) {
  if (hra) { 
    free(hra);
  }
}


//1. hra konci po zmiznuti hadika a zobrazia sa body
//2. hra konci ak vyprsi cas pre hru ktory sa definuje na zaciatku hry
/*
 * 2 typy svetov
 *
 * 1. bez prekazok, hadik prejde cez koniec mapy a da sa na opacnu stranu
 *
 * 2. s prekazkami(asi definuj suborom), vsetky ovocia sa musia dat zobrat
 *
 * hra konci ak hadik narazi do seba, prekazky alebo vyprsi cas
 *
 * hrac ktory vytvara svet definuje rozmery sveta(neplati pri subore) a cas pri hre s casom
 *
 *
 * treba zobrazovat cas a body
 *
 * hrac moze pozastavit hru, ak da pokracovat v hre po 3 sekundach sa zacne hybat
 *
 * hlavne menu - nova hra, pripojit k hre, pokracovat, koniec
 */

