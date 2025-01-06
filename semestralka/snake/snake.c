#include "snake.h"

Snake* vytvor_hada() {
  Snake* snake = (Snake*)malloc(sizeof(Snake));
  if (!snake) {
    printf("Snake sa nevytvoril\n");
    return NULL;
  }

  printf("@\n");

  snake->dlzka = 1;

  //treba este setupnut kde budu casti tela, cez rand() napr.

  return snake;
}

void pohni_hada(Snake* snake, int moveX, int moveY) {
  for (int i = snake->dlzka - 1; i > 0; i--) {
    snake->cast[i] = snake->cast[i-1];
  }
  snake->cast[0].x += moveX;
  snake->cast[0].y += moveY;
}

void zrus_hada(Snake* snake) {
  if (snake) {
    free(snake);
  }
}
