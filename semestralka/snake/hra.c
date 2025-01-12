#include "hra.h"

void vytvor_hru(Hra* hra, int riadky, int stlpce, int pocet_ovocia, int mod) {
  hra->riadky = riadky;
  hra->stlpce = stlpce;
  hra->pocet_ovocia = pocet_ovocia;
  hra->mod = mod;
  vytvor_hada(&hra->snake, riadky/2, stlpce/2);
  for (int i = 0; i < pocet_ovocia; i++) {
    hra->ovocie[i].zjedene = 1;
  }
  vytvor_ovocie(&hra->ovocie[0], riadky, stlpce);
  vytvor_plochu(hra->plocha, riadky, stlpce);
  hra->stavHry = 0;
  hra->cas = time(NULL);
  hra->limit = 30;
}


void updatni_hru(Hra* hra, int x, int y) {
  pohni_hada(&hra->snake, x, y, hra->riadky, hra->stlpce, hra->mod);

  time_t aktualny = time(NULL);
  if (difftime(aktualny, hra->cas) >= hra->limit) {
    hra->stavHry = 1;
    return;
  }
  
  for (int i = 0; i < hra->pocet_ovocia; i++) {
    if (!hra->ovocie[i].zjedene && zjedz_ovocie(&hra->snake, hra->ovocie[i].x, hra->ovocie[i].y)) {
      hra->ovocie[i].zjedene = 1;
      
      bool volne = false;
      for (int j = 0; j < hra->pocet_ovocia; j++) {
        if (hra->ovocie[j].zjedene) {
          volne = true;
          vytvor_ovocie(&hra->ovocie[j], hra->riadky, hra->stlpce);
          break;
        }
      }
      
      if (!volne) {
        break;
      }
    } 
  }

  if (hra->mod == 1) {
    if (hra->snake.cast[0].x < 0 || hra->snake.cast[0].x >=hra->stlpce || hra->snake.cast[0].y < 0 || hra->snake.cast[0].y >= hra->riadky) {
      hra->stavHry = 1;
    }
  }

  for (int i = 1; i < hra->snake.dlzka; i++) {
    if (hra->snake.cast[0].x == hra->snake.cast[i].x && hra->snake.cast[0].y == hra->snake.cast[i].y) {
      hra->stavHry = 1;
    }
  }
}


void vykresli_hru(Hra* hra) {
  vytvor_plochu(hra->plocha, hra->riadky, hra->stlpce);
  vykresli_ovocie(hra->ovocie, hra->plocha, hra->stlpce, 1);
  vykresli_hada(&hra->snake, hra->plocha, hra->stlpce);
  
  for (int i = 0; i < hra->riadky; i++) {
    move(i, 0);
    for (int j = 0; j < hra->stlpce; j++) {
      addch(hra->plocha[i * hra->stlpce + j]);
    }
  }

  time_t aktualny = time(NULL);
  int zostavajuci = hra->limit - difftime(aktualny, hra->cas);
  if (hra->stavHry == 0) { 
    mvprintw(hra->riadky, 0, "Zostavajuci cas: %d sekund\tSkore: %d", zostavajuci, hra->snake.dlzka * 100);
  } /*else {
    move(hra->riadky, 0);
    clrtoeol();
    if (zostavajuci == 0) {
      mvprintw(hra->riadky, 0, "\nUplynul cas!\nKonecne skore: %d\nPre ukoncenie programu stlac 'q'\n", hra->snake.dlzka * 100);
    } else {
      mvprintw(hra->riadky, 0, "\nPrehral si!\nKonecne skore: %d\nPre ukoncenie programu stlac 'q'\n", hra->snake.dlzka * 100);
    }
  }*/
  refresh();
}

