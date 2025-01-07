#include "hra.h"
#include <ncurses.h>
#include <string.h>
#include <time.h>

#define pocet_riadkov 10
#define pocet_stlpcov 10

int main(int argc, char *argv[]) {
  srand(time(NULL));
  Hra hra;
  int x = 0;
  int y = 0;

  initscr();
  noecho();
  timeout(100);

  vytvor_hru(&hra);

  while (!hra.stavHry) {
    int ch = getch();
    switch (ch) {
      case 'w': 
        x = 0;
        y = -1;
        break;
      case 'a': 
        x = -1;
        y = 0;
        break;
      case 's': 
        x = 0;
        y = 1;
        break;
      case 'd': 
        x = 1;
        y = 0;
        break;
    }
    updatni_hru(&hra, x, y);
    clear();
    vykresli_hru(&hra);
    printw("Aktualne skore: %d\n", hra.snake.dlzka * 100);
  }

  printw("Konecne skore: %d\n", hra.snake.dlzka * 100);
  getch();
  endwin();

  return 0;
}
