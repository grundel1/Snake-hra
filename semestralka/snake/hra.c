#include "hra.h"

int riadky = 30;
int stlpce = 30;
int pocet_ovocia = 256;

void vytvor_hru(Hra* hra) {
  vytvor_hada(&hra->snake, riadky/2, stlpce/2);
  for (int i = 0; i < pocet_ovocia; i++) {
    hra->ovocie[i].zjedene = 1;
  }
  vytvor_ovocie(&hra->ovocie[0], riadky, stlpce);
  vytvor_plochu(hra->plocha, riadky, stlpce);
  hra->stavHry = 0;
  hra->cas = time(NULL);
  hra->limit = 5;
}


void updatni_hru(Hra* hra, int x, int y) {
  pohni_hada(&hra->snake, x, y);

  time_t aktualny = time(NULL);
  if (difftime(aktualny, hra->cas) >= hra->limit) {
    hra->stavHry = 1;
    //printf("\nUPLNYUL CAS\nKONECNE SKORE %d", hra->snake.dlzka * 100);
    return;
  }
  
  for (int i = 0; i < pocet_ovocia; i++) {
    if (!hra->ovocie[i].zjedene && zjedz_ovocie(&hra->snake, hra->ovocie[i].x, hra->ovocie[i].y)) {
      hra->ovocie[i].zjedene = 1;
      
      bool volne = false;
      for (int j = 0; j < pocet_ovocia; j++) {
        if (hra->ovocie[j].zjedene) {
          volne = true;
          vytvor_ovocie(&hra->ovocie[j], riadky, stlpce);
          break;
        }
      }
      
      if (!volne) {
        break;
      }
    } 
  }

  if (hra->snake.cast[0].x == 0 || hra->snake.cast[0].x == stlpce - 1 || hra->snake.cast[0].y == 0 || hra->snake.cast[0].y == riadky - 1) {
    hra->stavHry = 1;
  }

  for (int i = 1; i < hra->snake.dlzka; i++) {
    if (hra->snake.cast[0].x == hra->snake.cast[i].x && hra->snake.cast[0].y == hra->snake.cast[i].y) {
      hra->stavHry = 1;
    }
  }
}


void vykresli_hru(Hra* hra) {
  vytvor_plochu(hra->plocha, riadky, stlpce);
  vykresli_ovocie(hra->ovocie, hra->plocha, stlpce, 1);
  vykresli_hada(&hra->snake, hra->plocha, stlpce);
  
  for (int i = 0; i < riadky; i++) {
    move(i, 0);
    for (int j = 0; j < stlpce; j++) {
      addch(hra->plocha[i * stlpce + j]);
    }
  }

  time_t aktualny = time(NULL);
  int zostavajuci = hra->limit - difftime(aktualny, hra->cas);
  if (hra->stavHry == 0) { 
    mvprintw(riadky, 0, "Zostavajuci cas: %d sekund\tSkore: %d", zostavajuci, hra->snake.dlzka * 100);
  } else {
    move(riadky, 0);
    clrtoeol();
    if (zostavajuci == 0) {
      mvprintw(riadky, 0, "\nUplynul cas!\nKonecne skore: %d", hra->snake.dlzka * 100);
      //printf("\nUplynul cas!\nKonecne skore: %d", hra->snake.dlzka * 100);
    } else {
      mvprintw(riadky, 0, "\nPrehral si!\nKonecne skore: %d", hra->snake.dlzka * 100);
      //printf("\nPrehral si!\nKonecne skore: %d", hra->snake.dlzka * 100);
    }
  }
  refresh();
}


/*
 * 2 typy svetov
 *
 * 1. bez prekazok, hadik prejde cez koniec mapy a da sa na opacnu stranu
 *
 * 2. s prekazkami, vsetky ovocia sa musia dat zobrat
 *
 * treba zobrazovat cas a body
 */

