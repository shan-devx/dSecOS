#ifndef __DG_DSECOS_H__
#define __DG_DSECOS_H__

#include <stdint.h>

extern void DG_Init();
extern void DG_DrawFrame();
extern void DG_SleepMs(uint32_t ms);
extern uint32_t DG_GetTicksMs();
extern int DG_GetKey(int *pressed, unsigned char *key);
extern void DG_SetWindowTitle(const char *title);

#endif
