#include "system.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vbe.h>
#include <shell.h>

extern uint8_t _binary_badapple_start[];
extern uint8_t _binary_badapple_end[];

void play_frame(uint8_t *ptr, uint8_t *screen){
  int s = 0;
  for(int i = 0; i < 640*400/8; i++){
    uint8_t a = ptr[i];

    for(int b = 7; b >= 0; b--){
      if((a >> b) & 1){
        screen[s++] = 0xFF;
        screen[s++] = 0xFF;
        screen[s++] = 0xFF;
        screen[s++] = 0;
      }
      else{
        screen[s++] = 0;
        screen[s++] = 0;
        screen[s++] = 0;
        screen[s++] = 0;
      }
    }
  }
}


void play_badapple(){
  uint8_t *apple = _binary_badapple_start;
  uint8_t *end = _binary_badapple_end;

  uint8_t *screen = (uint8_t *)malloc(640*400*4);
  if(screen == NULL){
    printf("malloc error");
    while(1);
  }

  while(apple < end && keyboard_keyf() != 'q'){
    play_frame(apple, screen);
    vbe_draw((char *)screen);
    apple += 640*400/8; // next frame
    time_wait(83);
  }
  vbe_clear();
  printf("dSecOS:~$ ");
  shell_run();
}
