#include "snake.h"

void vytvor_hada(Snake* snake, int x, int y) {
  snake->dlzka = 1;
  snake->cast[0].x = x;
  snake->cast[0].y = y;
}

void pohni_hada(Snake* snake, int moveX, int moveY, int riadky, int stlpce, int mod) {
  for (int i = snake->dlzka - 1; i > 0; i--) {
    snake->cast[i] = snake->cast[i - 1];
  }
  snake->cast[0].x += moveX;
  snake->cast[0].y += moveY;

  if (mod == 2) {
    if (snake->cast[0].x <= 0) {
      snake->cast[0].x = stlpce - 1;
    } else if (snake->cast[0].x >= stlpce - 1) {
      snake->cast[0].x = 0;
    }
    if (snake->cast[0].y <= 0) {
      snake->cast[0].y = riadky - 1;
    } else if (snake->cast[0].y >= riadky - 1) {
      snake->cast[0].y = 0;
    }
  }
}

void vykresli_hada(Snake* snake, char* plocha, int stlpce) {
  for (int i = snake->dlzka - 1; i > 0; i--) {
    plocha[snake->cast[i].y * stlpce + snake->cast[i].x] = '*';
  }
  plocha[snake->cast[0].y * stlpce + snake->cast[0].x] = '@';
}

bool zjedz_ovocie(Snake* snake, int ovocieX, int ovocieY) {
  if (snake->cast[0].x == ovocieX && snake->cast[0].y == ovocieY) {
    if (snake->dlzka < MAX_DLZKA) {
      snake->dlzka++;
    }
    return true;
  }
  return false;
}
