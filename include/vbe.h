#ifndef VBE_H
#define VBE_H

#define WIDTH 640
#define HEIGHT 400

extern void vbe_init();
extern void put_pixel(int x, int y, int b, int g, int r);
extern void put_char(int character);
extern void put_string(const char* c);
extern void vbe_draw(char *d);
extern void vbe_clear();
extern void vbe_backspace();

#endif
