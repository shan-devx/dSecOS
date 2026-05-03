#include "system.h"
#include <strings.h>
#include <vbe.h>

char *lfb;

void vbe_init(){
  lfb = (char *)(*(int *)0x9300);
}

void put_pixel(int x, int y){
  int i = ((y*WIDTH) + x) * 4;

  // bgax
  lfb[i] = 0xFF;
  lfb[i+1] = 0xFF;
  lfb[i+2] = 0xFF;
  lfb[i+3] = 0;
}
