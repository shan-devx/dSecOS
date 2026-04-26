#include <stddef.h>
#include <stdlib.h>
#include <system.h>
#include <string.h>
#include <strings.h>

void* memcpy(void *dest, const void *src, size_t count){
  const unsigned char *s = (const unsigned char *) src;
  unsigned char *d = (unsigned char *) dest;

  for(;count > 0; count--){
    *d++ = *s++;
  }

  return dest;
}

// temp
void *memmove(void *dest, const void *src, size_t n){
  void* t = malloc(n);
  memcpy(t, src, n);
  void* ret = memcpy(dest, t, n);
  free(t);
  return ret;
}

void *memset(void *dest, int val, size_t count){
  unsigned char *d = (unsigned char *) dest;

  for(; count > 0; count--){
    *d++ = val;
  }

  return dest;
}

void *memsetw(void *dest, int val, size_t count){
  unsigned short *d = (unsigned short*) dest;

  for(; count > 0; count--){
    *d++ = val;
  }

  return dest;
}

size_t strlen(const char *str){
  size_t out = 0;
  while(*str++ != '\0') out++;

  return out;
}

char* strncpy(char *dest, const char* src, size_t cnt){
  char *c = dest;
  
  while(cnt > 0){
    *c = *src;
    c++;
    if(*src != '\0') src++;
    cnt--;
  }

  return dest;
}

char* strcpy(char *dest, const char *src){
  return strncpy(dest, src, strlen(src) + 1);
}

char* strdup(const char *c){
  char* n = (char *)kmalloc((strlen(c) + 1));
  strcpy(n, c);
  return n;
}

int strncmp(const char *s1, const char *s2, size_t n){
  for(size_t i = 0; i < n; i++){
    char a = *(s1+i);
    char b = *(s2+i);

    if(a == '\0' && b == '\0') return 0;
    else if(a == '\0') return -1;
    else if(b == '\0') return 1;
    else{
      if(a != b) return a-b;
    };
  }
  return 0;
}
int strcmp(const char *s1, const char *s2){
  size_t s1n = strlen(s1);
  size_t s2n = strlen(s2);
  size_t mx = s1n > s2n ? s1n : s2n;

  return strncmp(s1, s2, mx);
}

int strncasecmp(const char *s1, const char *s2, size_t n){
  for(size_t i = 0; i < n; i++){
    char a = *(s1+i);
    char b = *(s2+i);

    if(a == '\0' && b == '\0') return 0;
    else if(a == '\0') return -1;
    else if(b == '\0') return 1;
    else{
      a |= 32;
      b |= 32;
      if(a != b) return a-b;
    };
  }

  return 0;
};
int strcasecmp(const char *s1, const char *s2){
  size_t s1n = strlen(s1);
  size_t s2n = strlen(s2);
  size_t mx = s1n > s2n ? s1n : s2n;

  return strncasecmp(s1, s2, mx);
}

char *strchr(const char *s, int c){
  while(*s != '\0'){
    if(*s == c) return (char *)s;
    s++;
  }

  return NULL;
}

char *strrchr(const char *s, int c){
  size_t size = strlen(s);

  for(char *i = (char *)s + size; i >= s; i--){
    if(*i == (char)c) return i;
  }

  return NULL;
}

int isspace(int c){
  char cr = c;
  if(cr == ' ' || cr == '\n' || cr == '\f' || cr == '\r' || cr == '\t' || cr == '\v') return 1;

  return 0;
}

int toupper(int c){
  if((char)c >= 'a' && (char)c <= 'z') return c & ~32;
  
  return c;
}

char *strstr(const char *haystack, const char *needle){
  int len1 = strlen(haystack);
  int len2 = strlen(needle);
  for(int i = 0; i <= len1 - len2; i++){
    if(strncmp(haystack + i, needle, len2) == 0) {
      return (char*) haystack + i;
    }
  }
  return NULL;
}
