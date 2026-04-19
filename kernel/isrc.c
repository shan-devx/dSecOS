#include "system.h"
#include <stdint.h>

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void (*isr_name[32])() = {isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7, isr8, isr9, isr10,
  isr11, isr12, isr13, isr14, isr15, isr16, isr17, isr18, isr19, isr20,
  isr21, isr22, isr23, isr24, isr25, isr26, isr27, isr28, isr29, isr30,
  isr31};

void isr_init(){
  for(int i = 0; i < 32; i++){
    idt_add(i, (uint32_t)isr_name[i], 0x08, 0x8E); // 0x8 => code segment, 0x8E => 10001110 (P(1), max privellage(000), Interrupt gate(1110)
  }
}

char *error_msg[] = {
"Division By Zero",
"Debug",
"Non Maskable Interrupt",
"Breakpoint",
"Into Detected Overflow",
"Out of Bounds",
"Invalid Opcode",
"No Coprocessor",
"Double Fault",
"Coprocessor Segment Overrun",
"Bad TSS",
"Segment Not Present",
"Stack Fault",
"General Protection Fault",
"Page Fault",
"Unknown Interrupt",
"Coprocessor Fault",
"Alignment Check",
"Machine Check",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved",
"Reserved"   
};

void isr_handler(struct reg *r){
  if(r->isr_no <32){
    terminal_print_string("[ERROR] ");
    terminal_print_string(error_msg[r->isr_no]);

    while(1);
  }
}
