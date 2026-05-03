#include "system.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <vbe.h>
#include "../doomgeneric/doomgeneric.h"

// for I/O
uint8_t inportb (uint16_t port){
    uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (port) : "memory");
    return rv;
}
void outportb (uint16_t port, uint8_t data){
    __asm__ __volatile__ ("outb %0, %1" : : "a"(data), "dN" (port) : "memory");
}

void main() __attribute__((section(".text.main")));
void main(){

  idt_init();
  isr_init();
  irq_init();
  time_install();
  keyboard_init();
  heap_init();
  __asm__ __volatile__("sti");
  vbe_init();
  wad_init();

  char *argv[] = {"doom", "-iwad", "freedoom1.wad"};
  doomgeneric_Create(3, argv);
  while(1){
    doomgeneric_Tick();
  }

  while(1);
}
