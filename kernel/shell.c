#include "system.h"
#include <stdio.h>
#include <vbe.h>
#include <strings.h>
#include "../doomgeneric/doomgeneric.h"
#include <kbadapple.h>

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
    bidx = 0;
  }

  else if(strncmp(shell_buff, "badapple", 8) == 0){
    bidx = 0;
    shell_buff[bidx] = '\0';
    play_badapple();
  }

  else if(strncmp(shell_buff, "echo ", 5) == 0){
    printf("\n");
    printf(shell_buff + 5);
    printf("\n");
    printf("dSecOS:~$ ");
    bidx = 0;
  }

  else if(strncmp(shell_buff, "clear", 5) == 0){
    vbe_clear();
    printf("dSecOS:~$ ");
    bidx = 0;
  }

  else if(strncmp(shell_buff, "hack", 4) == 0){
    color_hacker();

    printf("\n[HACK TOOL] v0.68\n");
    time_wait(500);
    printf("\nInitializing hack tool sequence...\n");
    time_wait(500);
    printf("\nScanning for targets...\n");
    time_wait(500);
    printf("\n >>> 192.168.42.7\n");
    time_wait(500);
    printf("\nBypassing firewall...\n");
    time_wait(700);
    printf("\n[FAILED] trying again...\n");
    time_wait(1000);
    printf("\nACCESS GRANTED\n");
    time_wait(500);
    printf("\nWelcome dSecOS User\n");
    time_wait(500);
    printf("\nConnecting to the servers\n");
    time_wait(500);
    printf("\nDownloading Stuff...\n");
    time_wait(1000);
    printf("\nDownloaded 69PB data\n");
    time_wait(500);
    printf("\n[Found] the files\n");
    time_wait(500);
    printf("\nUploading rootkit...\n");
    time_wait(500);
    printf("\nTrace deteced !!! BLASTING TARGET SERVERS ...\n");
    time_wait(1000);
    printf("\nTrace neutralized\n");
    time_wait(2000);
    printf("\njk nothing happened\n");

    color_white();
    printf("dSecOS:~$ ");
    bidx = 0;
  }

  else{
    printf("\nUnknown cmd\n");
    printf("dSecOS:~$ ");
    bidx = 0;
  }

  shell_buff[bidx] = '\0';
}

void shell_run(){
  printf(" dSecOS:~$ ");

  while(1){
    char c = keyboard_key();

    if(c == '\n'){
      shell_exc();
    }
    else if(c == '\b'){
      if(bidx > 0){
        vbe_backspace();

        bidx--;
        shell_buff[bidx] = '\0';
      }
    }
    else{
      put_char((int)c);
      shell_buff[bidx] = c;
      bidx++;
      shell_buff[bidx] = '\0';
    }
  }
}

