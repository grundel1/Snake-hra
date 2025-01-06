#include "ovocie.h"


Ovocie* vytvor_ovocie() {
  Ovocie* ovocie = (Ovocie*)malloc(sizeof(Ovocie));
  if(!ovocie) {
    printf("Nevytvorilo sa ovocie");
    return NULL;
  }
  printf("+\n");
  ovocie->zjedene = false;
  return ovocie;
}

void zrus_ovocie(Ovocie* ovocie) {
  if(ovocie) {
    free(ovocie);
  }
}
