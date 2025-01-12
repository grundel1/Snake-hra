#include "hra.h"
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <wait.h>
#include <fcntl.h>

typedef struct Data {
  int server_pipe[2];
  int klient_pipe[2];
  pthread_mutex_t mutex;
  int stop;
  int had;
} Data;

void* pouzivatel_vstup(void* arg) {
  Data* pipe_write = (Data*)arg;
  int x = 0;
  int y = 0;

  while (!pipe_write->stop) {
    int ch = getch();
    pthread_mutex_lock(&pipe_write->mutex);
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
        case 'q':
          pipe_write->stop = 1;
          pthread_mutex_unlock(&pipe_write->mutex);
          break;
        default:
          pthread_mutex_unlock(&pipe_write->mutex);
          continue;
    }
    write(pipe_write->klient_pipe[1], &x, sizeof(int));
    write(pipe_write->klient_pipe[1], &y, sizeof(int));
    pthread_mutex_unlock(&pipe_write->mutex);
  }
  return NULL;
}

void* vykreslovanie_plochy(void* arg) {
  Data* pipe_read = (Data*)arg;
  Hra hra;
  while (!pipe_read->stop) {
    if (read(pipe_read->server_pipe[0], &hra, sizeof(Hra)) > 0){
      vykresli_hru(&hra);
      pipe_read->had = hra.snake.dlzka * 100;
      refresh();
    }
    if (hra.stavHry != 0) {
      pipe_read->stop = 1;
      break;
    }
  }
  return NULL;
}

void server(Data* data, int riadky, int stlpce, int pocet_ovocia, int mod) {
  Hra hra;
  vytvor_hru(&hra, riadky, stlpce, pocet_ovocia, mod);
  hra.mod = mod;
  int x = 0;
  int y = 0;
  int pos_x = 0;
  int pos_y = 0;
  write(data->server_pipe[1], &hra, sizeof(Hra));

  int flags = fcntl(data->klient_pipe[0], F_GETFL, 0);
  fcntl(data->klient_pipe[0], F_SETFL, flags | O_NONBLOCK);

    
  while (hra.stavHry == 0) {
    int result_x = read(data->klient_pipe[0], &x, sizeof(int));
    int result_y = read(data->klient_pipe[0], &y, sizeof(int));

    if (result_x <= 0 || result_y <= 0) {
      pos_x = x;
      pos_y = y;
    }

    updatni_hru(&hra, pos_x, pos_y);
    write(data->server_pipe[1], &hra, sizeof(Hra));
    usleep(100000);
  }
  write(data->server_pipe[1], &hra, sizeof(Hra));
}

int menu() {
  int vyber = 0;
  while (1) {
    printf("\nVitaj v hre Snake\n\n");
    printf("MENU\n1. Nova hra\n2. Koniec\n");
    if (scanf("%d", &vyber) != 1) {
      printf("Zly vstup. Zadaj spravnu hodnotu!\n");
      while (getchar() != '\n') {
      }
    }
    if (vyber == 1 || vyber == 2) {
      break;
    } else {
      printf("Zly vstup. Zadaj spravnu hodnotu!\n");
    }
  }
  return vyber;
}


int main(int argc, char *argv[]) {
  srand(time(NULL));
  Data data;
  pthread_mutex_init(&data.mutex, NULL);
  data.stop = 0;

  if (menu() == 2) {
    pthread_mutex_destroy(&data.mutex);
    return 0;
  }
  
  int modHry = 0;
  printf("\nVyber si mod hry\n1. Klasicky mod\n2. Prechadzanie cez steny\n");
  while (1) {
    if (scanf("%d", &modHry) != 1) {
      printf("Zly vstup. Zadaj spravnu hodnotu!\n"); 
      while (getchar() != '\n') {
      }
    }
    if (modHry == 1 || modHry == 2) {
      break;
    } else {
      printf("Zly vstup. Zadaj spravnu hodnotu!\n"); 
    }
  }
  
  pipe(data.server_pipe);
  pipe(data.klient_pipe);
  int riadky = 20;
  int stlpce = 20;
  int pocet_ovocia = 256;

  if (fork() == 0) {
    close(data.server_pipe[0]);
    close(data.klient_pipe[1]);
    server(&data, riadky, stlpce, pocet_ovocia, modHry);
    exit(0);
  } else {
    close(data.server_pipe[1]);
    close(data.klient_pipe[0]);

    initscr();
    noecho();
    cbreak();
    timeout(100); 
    
    pthread_t vstup;
    pthread_t vykreslovanie;

    pthread_create(&vstup, NULL, pouzivatel_vstup, &data);
    pthread_create(&vykreslovanie, NULL, vykreslovanie_plochy, &data);

    pthread_join(vstup, NULL);
    pthread_join(vykreslovanie, NULL);

    endwin();
    wait(NULL);
  }
  pthread_mutex_destroy(&data.mutex);
  printf("Koniec hry! Tvoje konecne skore: %d\n", data.had);
  return 0;
}
