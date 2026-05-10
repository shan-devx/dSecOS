#include "system.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vbe.h>

extern uint8_t __disk_end;

struct Data{
  uint32_t count;
  uint8_t color;
  uint8_t check;
}__attribute__((packed));


void play_badapple(){
  struct Data *apple = (struct Data *) (__disk_end+1);
  struct Data *end = apple + 1329891;

  char *screen = (char *)malloc(640*400*4);
  if(screen == NULL){
    printf("malloc error");
    while(1);
  }

  size_t sidx = 0;
  while(apple < end){
    uint32_t cnt = apple->count;
    uint8_t clr = apple->color;
    uint8_t c = apple->check;

    while(cnt){
      size_t i = sidx * 4;
      if(clr == 0){
        screen[i] = 0;
        screen[i+1] = 0;
        screen[i+2] = 0;
        screen[i+3] = 0;
      }
      else if(clr == 1){
        screen[i] = 0xFF;
        screen[i+1] = 0xFF;
        screen[i+2] = 0xFF;
        screen[i+3] = 0;
      }

      cnt--;
      sidx++;
    }

    if(c == 255){
      sidx = 0;
      printf("1");
     // vbe_draw((char *)screen);
    }

    apple++;
  }

}
