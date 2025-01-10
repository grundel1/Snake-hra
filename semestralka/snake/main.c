#include "hra.h"
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <wait.h>
#include <fcntl.h>

int server_pipe[2];
int klient_pipe[2];
pthread_mutex_t mutex;

void* pouzivatel_vstup(void* arg) {
  int* pipe_write = (int*)arg;
  int x = 0;
  int y = 0;

  while (1) {
    int ch = getch();
    pthread_mutex_lock(&mutex);
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
          pthread_mutex_unlock(&mutex);
          continue;
    }
    write(pipe_write[1], &x, sizeof(int));
    write(pipe_write[1], &y, sizeof(int));
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(NULL);
  return NULL;
}

void* vykreslovanie_plochy(void* arg) {
  int* pipe_read = (int*)arg;
  Hra hra;

  while (1) {
    read(pipe_read[0], &hra, sizeof(Hra));
    vykresli_hru(&hra);
    //printw("Aktualne skore: %d\n", hra.snake.dlzka * 100);
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
  int x = 0;
  int y = 0;
  write(server_pipe[1], &hra, sizeof(Hra));

  int flags = fcntl(klient_pipe[0], F_GETFL, 0);
  fcntl(klient_pipe[0], F_SETFL, flags | O_NONBLOCK);

  while (hra.stavHry == 0) {
    int result_x = read(klient_pipe[0], &x, sizeof(int));
    int result_y = read(klient_pipe[0], &y, sizeof(int));

    if (result_x <= 0 || result_y <= 0) {
      x = x;
      y = y;
    }

    updatni_hru(&hra, x, y);
    write(server_pipe[1], &hra, sizeof(Hra));
    usleep(100000);
  }
  write(server_pipe[1], &hra, sizeof(Hra));
}

int menu() {
  int vyber = 0;
  printf("\nVitaj v hre Snake\n\n");
  printf("MENU\n1. Nova hra\n2. Koniec\n");
  scanf("%d", &vyber);
  return vyber;
}


int main(int argc, char *argv[]) {
  srand(time(NULL));
  pthread_mutex_init(&mutex, NULL);

  if (menu() == 2) {
    pthread_mutex_destroy(&mutex);
    return 0;
  }

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

    Hra hra;
    while (1) {
      read(server_pipe[0], &hra, sizeof(Hra));
      if (hra.stavHry != 0) {
        break;
      }
    }

    //pthread_cancel(vstup);
    //pthread_cancel(vykreslovanie);
    pthread_join(vstup, NULL);
    pthread_join(vykreslovanie, NULL);

    endwin();
    wait(NULL);
  }
  pthread_mutex_destroy(&mutex);
  return 0;
}
