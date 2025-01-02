#include <stdio.h>

#define pocet_riadkov 10
#define pocet_stlpcov 10

int main(int argc, char *argv[])
{ 
  char plocha[pocet_riadkov * pocet_stlpcov];

  for (int i = 0; i < pocet_riadkov; i++) {
    for (int j = 0; j < pocet_stlpcov; j++) {
      printf("xxxx\n");
      //tu sa vykresli mapka
    }
  }
  return 0;
}
