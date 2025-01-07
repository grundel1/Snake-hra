#include "plocha.h"

void vytvor_plochu(char* plocha, int riadky, int stlpce) {
  for (int i = 0; i < riadky; i++) {
    for (int j = 0; j < stlpce; j++) {
      plocha[i * stlpce + j] = (j == 0 || i == 0 || j == stlpce -1 || i == riadky - 1) ? '#' : ' ';
    }
  }
}

void vykresli_plochu(char* plocha, int riadky, int stlpce) {
  for (int i = 0; i < riadky; i++) {
    for (int j = 0; j < stlpce; j++) {
      putchar(plocha[i * stlpce + j]);
    }
    putchar('\n');
  }
}
