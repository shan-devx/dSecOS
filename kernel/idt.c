#include "system.h"
#include <stdint.h>

struct idt32{
   uint16_t offset1;
   uint16_t selector; // code segment
   uint8_t  zero;
   uint8_t  flags; // Gate type, DPL(privilege level), P(present)
   uint16_t offset2;
} __attribute__((packed)); // to avoid padding by gcc

struct idt_ptr{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct idt32 idt[256];
struct idt_ptr idtp;

extern void idt_load(struct idt_ptr* ptr);

void idt_add(uint8_t numb, uint32_t offset, uint16_t selc, uint8_t af){
  idt[numb].offset1 = offset;
  idt[numb].offset2 = offset >> 16;
  idt[numb].selector = selc;
  idt[numb].flags = af;
  idt[numb].zero = 0;
}

void idt_init(){
    idtp.limit = (sizeof(struct idt32) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    memset((unsigned char *)&idt, 0, sizeof(struct idt32) * 256);

    idt_load(&idtp);
}
