#include "system.h"
#include <stdio.h>
#include <vbe.h>
#include <strings.h>
#include "../doomgeneric/doomgeneric.h"

char shell_buff[630];
size_t bidx = 0;

extern volatile int doom_run;

void shell_exc(){
  if(strncmp(shell_buff, "doom", bidx) == 0){
    doom_run = 1;
    char *argv[] = {"doom", "-iwad", "freedoom1.wad"};
    doomgeneric_Create(3, argv);
    while(doom_run){
      doomgeneric_Tick();
    }

    vbe_clear();
    printf("dSecOS:~$ ");

  }

  else if(strncmp(shell_buff, "echo ", 5) == 0){
    printf("\n");
    printf(shell_buff + 5);
    printf("\n");
    printf("dSecOS:~$ ");
    bidx = 0;
  }

  else{
    printf("\nUnknown cmd\n");
    printf("dSecOS:~$ ");
    bidx = 0;
  }
}

void shell_run(){
  printf("dSecOS:~$ ");

  while(1){
    char c = keyboard_key();

    if(c == '\n'){
      shell_exc();
    }
    else{
      shell_buff[bidx] = c;
      bidx++;
      put_char((int)c);
    }
  }
}

