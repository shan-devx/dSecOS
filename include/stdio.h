#ifndef __STDIO_H__
#define __STDIO_H__

#include <stdarg.h>
#include <stddef.h>

typedef struct{
  char *base; // start
  char *ptr; // curren position
  size_t size;
  char mode; 
} FILE;

extern FILE *stderr;
extern FILE *stdout;
extern FILE *stdin;

int sscanf(const char *str, const char *format, ...);

int printf(const char  *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int puts(const char *s);
int putchar(int c);

int vsnprintf(char *str, size_t size, const char *format, va_list ap);
int snprintf(char *str, size_t size, const char *format, ...);

FILE *fopen(const char *pathname, const char *mode);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
int fclose(FILE *stream);


#define SEEK_CUR 0
#define SEEK_END 1
#define SEEK_SET 2
int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);

int remove(const char *pathname);
int rename(const char *oldpath, const char *newpath);

#endif
