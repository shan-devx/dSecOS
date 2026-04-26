#include "system.h"
#include <stddef.h>
#include <stdint.h>

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
  terminal_init();
  idt_init();
  isr_init();
  irq_init();
  __asm__ __volatile__("sti");
  time_install();
  keyboard_init();
  heap_init();
  void *ptr = kmalloc(1000);
  if (ptr == 0){
    terminal_print_string("error");
  }
  else{
    terminal_print_string("worked ig");
  }
//  __asm__ __volatile__("div %0" :: "r"(0));
  
  while(1);
}
