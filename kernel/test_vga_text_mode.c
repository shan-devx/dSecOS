#include "system.h"
#include <stddef.h>
#include <stdint.h>

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg){
  return bg << 4 | fg;
}

static inline uint16_t vga_entry(unsigned char c, uint8_t color){
  return color << 8 | c;
}

size_t terminal_column;
size_t terminal_row;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*) VGA_MEMORY;

void terminal_init(){
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_LIGHT_GREEN);

  terminal_column = 0;
  terminal_row = 0;
  for(size_t r = 0; r < VGA_HEIGHT; r++){
    for(size_t c = 0; c < VGA_WIDTH; c++){
      terminal_buffer[VGA_WIDTH * r + c] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_print_string(const char* c){
  size_t i = 0;
  while(c[i]){
    const size_t idx = terminal_row * VGA_WIDTH + terminal_column;
    terminal_buffer[idx] = vga_entry(c[i], terminal_color);

    if(++terminal_column == VGA_WIDTH){
      terminal_column = 0;
      if(++terminal_row == VGA_HEIGHT){
        terminal_row = 0;
      }
    }

    i++;
  }
}

void kernel_main() __attribute__((section(".text.kernel_main"))); // define subpart of .text so that it could be assigned first
void kernel_main(){
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_LIGHT_GREEN);
  terminal_init();

  //terminal_print_string("Hello this is vga screen");

  while(1);
}
