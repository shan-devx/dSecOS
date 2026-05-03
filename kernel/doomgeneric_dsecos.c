#include "../doomgeneric/doomgeneric.h"
#include <stdio.h>
#include <stdlib.h>
#include <system.h>
#include <stdint.h>
#include <vbe.h>

void DG_Init() {
}

void DG_DrawFrame() {
  vbe_draw((char *)DG_ScreenBuffer);
}

void DG_SleepMs(uint32_t ms) {
  time_wait(ms);
}

uint32_t DG_GetTicksMs() {
  return time_tick;
}

int DG_GetKey(int *pressed, unsigned char *key) {
    return doom_keyboard(pressed, key);
}

void DG_SetWindowTitle(const char *title) {
}

extern char _binary_freedoom1_wad_start[];
extern char _binary_freedoom1_wad_end[];

void wad_init(){
  FILE *wad = malloc(sizeof(FILE));
  wad->base = _binary_freedoom1_wad_start;
  wad->ptr = _binary_freedoom1_wad_start;
  wad->size = _binary_freedoom1_wad_start - _binary_freedoom1_wad_start;
  wad->mode = 'r';

  file_names[file_cnt] = "freedoom1.wad";
  disk[file_cnt] = wad;
  file_cnt++;
}
