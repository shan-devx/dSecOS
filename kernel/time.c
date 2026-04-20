#include "system.h"

int time_tick = 0;

void time_handler(struct reg *r){
  time_tick++;

  if(time_tick % 100 == 0){
    terminal_print_string(" 1 sec passed ");
  }
}

void time_wait(int ticks){
  int ftick = time_tick + ticks;
  while(time_tick < ftick);
}

void time_install(){
  int d = 1193180 / 100;
  outportb(0x43, 0x36);
  outportb(0x40, d & 0xFF);
  outportb(0x40, d >> 8);

  irq_install(0, time_handler);
}
