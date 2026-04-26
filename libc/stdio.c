#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <system.h>
#include <stdio.h>
#include <strings.h>

#define STB_SPRINTF_IMPLEMENTATION
#include <stb_sprintf.h>

int errno = 0;

extern uint8_t __disk_start;
extern uint8_t __disk_end;

FILE *stderr = NULL;
FILE *stdout = NULL;
FILE *stdin = NULL;

int sscanf(const char *str, const char *format, ...){
  return 0;
}

int printf(const char  *format, ...){
  terminal_print_string(format);
  return 0;
}

int puts(const char *s){
  printf(s);
  return 0;
}

int putchar(int c){
  char buf[2] = {(char)c, '\0'};
  terminal_print_string(buf);
  return c;
}

int vsnprintf(char *str, size_t size, const char *format, va_list ap){
  return stbsp_vsnprintf(str, size, format, ap);
}

int fprintf(FILE *stream, const char *format, ...){
  return 0;
}

int snprintf(char *str, size_t size, const char *format, ...){
  va_list args;
  va_start(args, format);
  int ret = stbsp_vsnprintf(str, size, format, args);
  va_end(args);

  return ret;
}

// fake file system 
FILE *disk[10];
char* file_names[10];
size_t file_cnt = 0;

int idx_name(const char * c){
  for(size_t i = 0; i < file_cnt; i++){
    if(!strcmp(c, file_names[i])){
      return i;
    }
  }

  return -1;
}

FILE *fopen(const char *pathname, const char *mode){
  static uint32_t end_pos = 0;
  if(strchr(mode, 'r')){
    int idx = idx_name(pathname);

    if(idx >= 0){
      FILE *file = (FILE *)malloc(sizeof(FILE));
      file->base = disk[idx]->base;
      file->mode = disk[idx]->mode;
      file->size = disk[idx]->size;
      file->ptr = disk[idx]->ptr;

      return file;
    }
    else return NULL;
  }
  else if(strchr(mode, 'w')){
    int idx = idx_name(pathname);

    if(idx >= 0){
      FILE *file = (FILE *)malloc(sizeof(FILE));
      file->base = disk[idx]->base;
      file->ptr = file->base;
      file->size = disk[idx]->size;
      file->mode = 'w';

      return file;
    }

    FILE *nw = malloc(sizeof(FILE));
    end_pos += 1024 * 1024; // 1mb each file
    size_t sz = &__disk_end - &__disk_start;
    if(end_pos > sz) return NULL;

    nw->mode = 'w';
    nw->base = (char *)(&__disk_end - end_pos);
    nw->ptr = nw->base;
    nw->size = 1024 * 1024;

    file_names[file_cnt] = (char *)malloc(strlen(pathname) + 1);
    strcpy(file_names[file_cnt], pathname);
    disk[file_cnt] = nw;
    file_cnt++;
    return nw;
  }

  return NULL;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream){
  return 0;
}

int rename(const char *oldpath, const char *newpath){
  int idx = idx_name(oldpath);
  if(idx == -1) return -1;
  char *nw = (char *)malloc(strlen(newpath) + 1);
  if(nw == NULL) return -1;

  strcpy(nw, newpath);
  file_names[idx] = nw;

  return 0;
}

int remove(const char *filename){
  return rename(filename, '\0');
}

int fclose(FILE *stream){
  free(stream);
  return 0;
}

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream){
  size_t bytes = nmemb * size;
  size_t rem = stream->size - (stream->ptr - stream->base);
  if(rem < bytes) bytes = rem;

  memcpy(ptr, stream->ptr, bytes);
  stream->ptr += bytes;

  return nmemb;
}

int fseek(FILE *stream, long off, int whence){
  if (whence == SEEK_SET) stream->ptr = stream->base + off;
  else if (whence == SEEK_CUR) stream->ptr += off;
  else if (whence == SEEK_END) stream->ptr = stream->base + stream->size + off;

  return 0;
}

long ftell(FILE *stream){
  return stream->ptr - stream->base;
}
