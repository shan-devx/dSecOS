#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <stddef.h>
#include <stdint.h>

struct reg{
  uint32_t gs, fs, es, ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pusha
  uint32_t isr_no, err_c;
  uint32_t eip, cs, eflags, useresp, ss; // automatically pused (useresp is not setuped yet)
};


extern unsigned char *memcpy(unsigned char *dest, const unsigned char *src, size_t count);
extern unsigned char *memset(unsigned char *dest, unsigned char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern uint8_t inportb (uint16_t port);
extern void outportb (uint16_t port, uint8_t data);
static inline void io_wait(void){
    outportb(0x80, 0); // wait for few millisec (for slow hardware)
}


extern void idt_add(uint8_t numb, uint32_t offset, uint16_t selc, uint8_t af);
extern void idt_init();

extern void isr_init();

extern void irq_init();
extern void irq_install(int i, void (*handler)(struct reg *r));
extern void irq_uninstall(int i);

extern int time_tick;
extern void time_install();
extern void time_wait(int ticks);

extern void keyboard_init();

extern void terminal_init();
extern void terminal_print_string(const char* c);

#endif
