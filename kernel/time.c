#include "system.h"
#include <stdio.h>

volatile int time_tick = 0;

void time_handler(struct reg *r){
  time_tick++;
/*
  if(time_tick % 1000 == 0){
    printf("***TIME IS WORKING*******");
  }
*/
}

void time_wait(int ticks){
  int ftick = time_tick + ticks;
  while(time_tick < ftick);
}

void time_install(){
  int d = 1193180 / 1000;
  outportb(0x43, 0x36);
  outportb(0x40, d & 0xFF);
  outportb(0x40, d >> 8);

  irq_install(0, time_handler);
}
