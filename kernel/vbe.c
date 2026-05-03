#include <stddef.h>
#include <system.h>
#include <strings.h>
#include <vbe.h>
#include <font8x8.h>

char *lfb;

void vbe_init(){
  lfb = (char *)(*(int *)0x9300);
}

size_t tcolumn;
size_t trow;

void put_pixel(int x, int y, int b, int g, int r){
  int i = ((y*WIDTH) + x) * 4;

  // bgax
  lfb[i] = b;
  lfb[i+1] = g;
  lfb[i+2] = r;
  lfb[i+3] = 0;
}

void put_char(int character, int x, int y){
  for(int i = 0; i < 8; i++){
    int ch = font8x8_basic[character][i];
    int j = 0;

    while(j < 7){
      if(ch & 1){
        put_pixel(x+j, y+i, 0xFF, 0xFF, 0xFF);
      }
      else{
        put_pixel(x+j, y+i, 0, 0, 0);
      }
      ch = ch >> 1;
      j++;
    }
  }
}

void put_string(const char* c){
  size_t i = 0;
  while(c[i]){
    put_char(c[i], tcolumn, trow);

    tcolumn += 8;
    if(tcolumn == WIDTH){
      trow += 8;
      tcolumn = 0;
      if(trow == HEIGHT){
        trow = 0;
      }
    }

    i++;
  }
}
