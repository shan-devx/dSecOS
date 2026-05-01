#include "../doomgeneric/doomgeneric.h"
#include <system.h>
#include <stdint.h>

void DG_Init() {
    // initialize your framebuffer here
}

void DG_DrawFrame() {
    // copy DG_ScreenBuffer to your framebuffer
    // DG_ScreenBuffer is the doom render buffer
}

void DG_SleepMs(uint32_t ms) {
    // busy wait or use your PIT timer
}

uint32_t DG_GetTicksMs() {
    // return milliseconds since boot
    // use your PIT timer
}

int DG_GetKey(int *pressed, unsigned char *key) {
    // return keyboard input
    return 0;  // stub for now
}

void DG_SetWindowTitle(const char *title) {
    // ignore or print to terminal
}
