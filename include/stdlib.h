#ifndef __STD_LIB_H__
#define __STD_LIB_H__

#include <stddef.h>

void* malloc(size_t s);
void free(void *p);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);

void exit(int status);

int atoi(const char *nptr);
double atof(const char *nptr);

int abs(int j);

int system(const char *command);

#endif
