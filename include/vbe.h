#ifndef VBE_H
#define VBE_H

#define WIDTH 320
#define HEIGHT 200

extern void vbe_init();
extern void put_pixel(int x, int y, int b, int g, int r);
extern void put_char(int character, int x, int y);
extern void put_string(const char* c);

#endif
