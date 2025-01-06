#include "plocha.h"

Plocha* vytvor_plochu() {
  Plocha* plocha = (Plocha*)malloc(sizeof(Plocha));
  if (!plocha) {
    return NULL;
  }
  
  plocha->vyska = 0;
  plocha->sirka = 0;
  plocha->svet = (char**)malloc(sizeof(char*) * plocha->vyska);
  return plocha;
}

bool nacitaj_plochu_subor(Plocha* plocha, const char* subor) {
  FILE* file = fopen(subor, "r");
  if (!file) {
    fprintf(stderr, "Nechcem sa nacitat\n");
    return false;
  }

  fscanf(file, "%d %d", &plocha->sirka, &plocha->vyska);

  for (int i = 0; i < plocha->vyska; i++) {
    plocha->svet[i] = (char*)malloc(sizeof(char) * (plocha->vyska + 1));    //robi memory leaky
    fscanf(file, "%s", plocha->svet[i]);
  }

  //fclose(file); //bez tohto mi to ide??
  return true;
}

void vykresli_plochu(Plocha* plocha) {
  for (int i = 0; i < plocha->vyska; i++) {
    printf("%s\n", plocha->svet[i]);
  }
}

void zrus_plochu(Plocha* plocha) {
  if (plocha->svet) {
    for (int i = 0; i < plocha->vyska + 1; i++) {
      free(plocha->svet[i]);
    }
    free(plocha->svet);
    free(plocha);
  } 
}
