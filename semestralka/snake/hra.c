#include "hra.h"

int riadky = 20;
int stlpce = 20;
int pocet_ovocia = 256;

void vytvor_hru(Hra* hra) {
  vytvor_hada(&hra->snake, riadky/2, stlpce/2);
  for (int i = 0; i < pocet_ovocia; i++) {
    hra->ovocie[i].zjedene = 1;
  }
  vytvor_ovocie(&hra->ovocie[0], riadky, stlpce);
  vytvor_plochu(hra->plocha, riadky, stlpce);
  hra->stavHry = 0;
}


void updatni_hru(Hra* hra, int x, int y) {
  pohni_hada(&hra->snake, x, y);
  
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
  //vykresli_plochu(hra->plocha, riadky, stlpce);
  
  for (int i = 0; i < riadky; i++) {
    move(i, 0);
    for (int j = 0; j < stlpce; j++) {
      addch(hra->plocha[i * stlpce + j]);
    }
  }

  move(riadky, 0);
  //printw("Skore: %d", hra->snake.dlzka * 100);
  refresh();
}

//2. hra konci ak vyprsi cas pre hru ktory sa definuje na zaciatku hry
/*
 * 2 typy svetov
 *
 * 1. bez prekazok, hadik prejde cez koniec mapy a da sa na opacnu stranu
 *
 * 2. s prekazkami(asi definuj suborom), vsetky ovocia sa musia dat zobrat
 *
 *
 * hrac ktory vytvara svet definuje rozmery sveta(neplati pri subore) a cas pri hre s casom
 *
 * treba zobrazovat cas a body
 *
 * hlavne menu - nova hra, pripojit k hre, pokracovat, koniec
 */

