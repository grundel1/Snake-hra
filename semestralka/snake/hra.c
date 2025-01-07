#include "hra.h"

int riadky = 20;
int stlpce = 20;

void vytvor_hru(Hra* hra) {
  vytvor_hada(&hra->snake, riadky/2, stlpce/2);
  vytvor_ovocie(&hra->ovocie, riadky, stlpce);
  vytvor_plochu(hra->plocha, riadky, stlpce);
  hra->stavHry = 0;
}


void updatni_hru(Hra* hra, int x, int y) {
  pohni_hada(&hra->snake, x, y);
  
  if (!hra->ovocie.zjedene && zjedz_ovocie(&hra->snake, hra->ovocie.x, hra->ovocie.y)) {
    hra->ovocie.zjedene = true;
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
  vykresli_ovocie(&hra->ovocie, hra->plocha, stlpce, 1);
  vykresli_hada(&hra->snake, hra->plocha, stlpce);
  vykresli_plochu(hra->plocha, riadky, stlpce);
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

