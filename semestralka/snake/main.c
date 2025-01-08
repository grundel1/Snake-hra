#include "hra.h"
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

int server_pipe[2];
int klient_pipe[2];
int spustena = 1;

void* pouzivatel_vstup(void* arg) {
  int* pipe_write = (int*)arg;
  int x = 0;
  int y = 0;

  while (1) {
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
        default:
          continue;
    }
    write(pipe_write[1], &x, sizeof(int));
    write(pipe_write[1], &y, sizeof(int));
  }
  return NULL;
}

void* vykreslovanie_plochy(void* arg) {
  int* pipe_read = (int*)arg;
  Hra hra;

  while (1) {
    read(pipe_read[0], &hra, sizeof(Hra));
    vykresli_hru(&hra);
    printw("Aktualne skore: %d\n", hra.snake.dlzka * 100);
    refresh();

    if (hra.stavHry != 0) {
      break;
    }
  }
  return NULL;
}

void server() {
  Hra hra;
  vytvor_hru(&hra);
  vykresli_hru(&hra);
  int x = 0;
  int y = 0;

  while (hra.stavHry == 0) {
    read(klient_pipe[0], &x, sizeof(int));
    read(klient_pipe[0], &y, sizeof(int));
    updatni_hru(&hra, x, y);
    write(server_pipe[1], &hra, sizeof(Hra));
  }
  write(server_pipe[1], &hra, sizeof(Hra));
}


int main(int argc, char *argv[]) {
  srand(time(NULL));

  pipe(server_pipe);
  pipe(klient_pipe);
  
  if (fork() == 0) {
    close(server_pipe[0]);
    close(klient_pipe[1]);
    server();
    exit(0);
  } else {
    close(server_pipe[1]);
    close(klient_pipe[0]);

    initscr();
    noecho();
    timeout(100); 
    
    pthread_t vstup;
    pthread_t vykreslovanie;

    pthread_create(&vstup, NULL, pouzivatel_vstup, (void*)klient_pipe);
    pthread_create(&vykreslovanie, NULL, vykreslovanie_plochy, (void*)server_pipe);

    pthread_join(vstup, NULL);
    pthread_join(vykreslovanie, NULL);

    endwin();
    wait(NULL);
  printf("Konecne skore: %d\n", 0);
  }
  printf("Konecne skore: %d\n", 0);
  return 0;
}
