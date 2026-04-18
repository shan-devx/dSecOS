#include "system.h"
#include <stddef.h>

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
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void main() __attribute__((section(".text.main")));
void main(){
  while(1);
}
