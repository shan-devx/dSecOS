#include "system.h"
#include <stdint.h>
#include "../doomgeneric/doomkeys.h"
#include <stdio.h>

// US keyboard layout
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

int press = 0;
unsigned char key_press = 0;

int doom_keyboard(int *pressed, unsigned char *key){
  if(key_press != 0){
    *pressed = press;

    switch(key_press){
      case 'w':
        *key = KEY_UPARROW;
        break;
      case 's':
        *key = KEY_DOWNARROW;
        break;
      case 'a':
        *key = KEY_LEFTARROW;
        break;
      case 'd':
        *key = KEY_RIGHTARROW;
        break;
      case '\n':
        *key = KEY_ENTER;
        break;
      default:
        *key = 0;
    }

    return 1;
  }
  return 0;
}

#define KB_D 0x60 // keyboard data register 
#define KB_C 0x64 // keyboard control register

void keyboard_handler(struct reg *r){
  uint8_t scancode = inportb(KB_D);
  // key released
  if(scancode & 0x80){
    press = 0;
    key_press = 0;
  }
  else{
    press = 1;
    key_press = kbdus[scancode];
  }
}

void keyboard_init(){
  irq_install(1, keyboard_handler);
}
