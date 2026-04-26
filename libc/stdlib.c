#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void exit(int status){
  printf("exit");
  while (1);
}

double pow(double x, double y){
  double ret = 1;
  while(y){
    ret *= x;
    y--;
  }

  return ret;
}

int atoi(const char *nptr){
  int s = 1, r = 0;
  if(*nptr == '-'){
    s = -1;
    nptr++;
  }
  else if(*nptr == '+'){
    nptr++;
  }

  while(*nptr != '\0'){
    if(*nptr >= '0' && *nptr <= '9'){
      r = (r*10) + (*nptr - '0');
    }
    if(*nptr == '.') return s*r;

    nptr++;
  }

  return s*r;
}

// :(
int cnt_dig(int a){
  int cnt = 0;
  if(a == 0) return 1;
  while(a != 0){
    a /= 10;
    cnt++;
  }

  return cnt;
}
double atof(const char *nptr){
  double a = atoi(nptr);
  printf("%lf\n", a);

  while(*nptr != '\0'){
    if(*nptr == '.'){
      nptr ++;

      int zeros = 0;
      while(*nptr == '0'){
        zeros++;
        nptr++;
      }
      if(zeros == 0) zeros = 1;

      int b = atoi(nptr);
      printf("%lf\n", pow(0.1, cnt_dig(b)));
      a += pow(0.1, cnt_dig(b)) * b * pow(0.1, zeros);

      return a;
    }

    nptr++;
  }

  return a;
}

int abs(int j){
  if(j < 0) return j * -1;

  return j;
}

double fabs(double x){
  if(x < 0) return x * -1;

  return x;
}

int system(const char *command){
  return -1;
}
