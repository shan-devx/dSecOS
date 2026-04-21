#include "system.h"
#include <stddef.h>
#include <stdint.h>

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, size_t count){
  const unsigned char *s = (const unsigned char *) src;
  unsigned char *d = (unsigned char *) dest;

  for(;count > 0; count--){
    *d++ = *s++;
  }

  return dest;
}

unsigned char *memset(unsigned char *dest, unsigned char val, size_t count){
  unsigned char *d = (unsigned char *) dest;

  for(; count > 0; count--){
    *d++ = val;
  }

  return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count){
  unsigned short *d = (unsigned short*) dest;

  for(; count > 0; count--){
    *d++ = val;
  }

  return dest;
}

size_t strlen(const char *str){
  size_t out = 0;
  while(*str++ != '\0') out++;

  return out;
}

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
//  __asm__ __volatile__("div %0" :: "r"(0));
  
  while(1);
}
