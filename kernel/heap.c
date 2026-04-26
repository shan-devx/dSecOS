#include "system.h"
#include <stddef.h>
#include <stdint.h>

#define HEAP_START 0x200000 // hard coded for now
#define HEAP_SIZE 0x4000000 // 64mb
#define HEAP_END (HEAP_START + HEAP_SIZE)

struct heap_header{
  int free;
  uint32_t size;
}__attribute__((packed));

#define HEADER_SIZE sizeof(struct heap_header)

void heap_init(){
  struct heap_header *start = (struct heap_header*) HEAP_START;
  start->free = 1;
  start->size = HEAP_SIZE - HEADER_SIZE; 

  struct heap_header *end = (struct heap_header *) HEAP_END;
  end->size = 0;
  end->free = 1;
}

void *kmalloc(size_t size_needed){
  struct heap_header *start = (struct heap_header *)HEAP_START;

  while(start->size != 0){
    if(start->free){
      if(start->size == size_needed){
        start->free = 0;

        return (void *)((uint8_t *)start + HEADER_SIZE);
      }

      else if(start->size > size_needed){
        struct heap_header *next = (struct heap_header *)((uint8_t *)start + HEADER_SIZE + size_needed);
        next->free = 1;
        next->size = start->size - size_needed - HEADER_SIZE;

        start->size = size_needed;
        start->free = 0;
        
        return (void *)((uint8_t *)start + HEADER_SIZE);
      }
    }
    
    start = (struct heap_header *)((uint8_t *)start + HEADER_SIZE + start->size);
  }

  return NULL;
}

void kfree(void *ptr){
  struct heap_header *loc = (struct heap_header *)((uint8_t *)ptr - HEADER_SIZE);
  loc->free = 1;

  struct heap_header *next = (struct heap_header *)((uint8_t *)loc + loc->size + HEADER_SIZE);
  while(next->size != 0 && next->free == 1){
    loc->size += HEADER_SIZE + next->size;
    
    next = (struct heap_header *)((uint8_t *) next + HEADER_SIZE + next->size);
  }
}
