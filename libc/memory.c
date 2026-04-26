#include "system.h"
#include <stddef.h>
#include <string.h>

extern void* kmalloc(size_t size_needed);
extern void kfree(void *ptr);

void* malloc(size_t s){
  return kmalloc(s);
}
void free(void *p){
  kfree(p);
  return;
}

void *calloc(size_t nmemb, size_t size){
  void* a = malloc(nmemb * size);
  if(a != NULL){
    memset(a, 0, nmemb*size);
  }

  return a;
}

void *realloc(void *ptr, size_t size){
  if(ptr == NULL) return malloc(size);

  void* nw = malloc(size);
  if(nw != NULL){
    memcpy(nw, ptr, strlen(ptr));
    free(ptr);
  }

  return nw;
}
