#ifndef __STRING_H__
#define __STRING_H__

#include <stddef.h>

void* memcpy(void *dest, const void *src, size_t count);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *dest, int val, size_t count);
void *memsetw(void *dest, int val, size_t count);

size_t strlen(const char *str);
char* strncpy(char *dest, const char* src, size_t cnt);
char* strcpy(char *dest, const char *src);
char* strdup(const char *c);

char *strrchr(const char *s, int c);
char *strchr(const char *s, int c);
char *strstr(const char *haystack, const char *needle);

#endif
