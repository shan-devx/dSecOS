#include "system.h"
#include <stdint.h>

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#define PICM_C 0x20 // PIC master cmd port
#define PICM_D 0x21 // PIC master data port
#define PICS_C 0xA0 // PIC slave cmd port
#define PICS_D 0xA1 // PIC slave data port

void *irq_routines[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void irq_install(int i, void (*handler)(struct reg *r)){
  irq_routines[i] = handler;
}
void irq_uninstall(int i){
  irq_routines[i] = 0;
}

void (*irq_name[32])() = {irq0, irq1, irq2, irq3,irq4, irq5, irq6, irq7, irq8, irq9, irq10,
  irq11, irq12, irq13, irq14, irq15};

void irq_init(){
  outportb(PICM_C, 0x11); // initialize 0x10 | additional info about env(ICW4) 0x01
  io_wait();
  outportb(PICS_C, 0x11);
  io_wait();

  // isr
  outportb(PICM_D, 32);
  io_wait();
  outportb(PICS_D, 40);
  io_wait();

  // wire PIC slave to master
  outportb(PICM_D, 0x4);
  io_wait();
  outportb(PICS_D, 0x2);
  io_wait();

  outportb(PICM_D, 0x01); // 8086 mode
  io_wait();
  outportb(PICS_D, 0x01); // 8086 mode
  io_wait();

  
  for(int i = 0; i < 16; i++){
    idt_add(i + 32, (uint32_t)irq_name[i], 0x08, 0x8E); // 0x8 => code segment, 0x8E => 10001110 (P(1), max privellage(000), Interrupt gate(1110)
  }
}

void irq_handler(struct reg *r){
  void (*handler)(struct reg *a);
  int i = r->isr_no - 32;
  handler = irq_routines[i];

  if(handler){
    handler(r);
  }

  // EOI (End of Interrupt)
  if(i >= 8){
    outportb(PICS_C, 0x20);
  }
  outportb(PICM_C, 0x20);
}
