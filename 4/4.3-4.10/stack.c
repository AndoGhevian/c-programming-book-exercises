
#include <stdio.h>
#include "calc.h"
#include "deftest.h" /* this header is for linker error test for multiple definitions in header */

#define SBUFSIZE 100

double sbuf[SBUFSIZE];
int sbufp = 0;

void push(double val) {
  if(sbufp < SBUFSIZE)
    sbuf[sbufp++] = val;
  else
    printf("stack is full, can't push\n");
}

double pop(void) {
  if(sbufp > 0)
    return sbuf[--sbufp];
  else {
    printf("stack is empty\n");
    return 0.0;
  }
}

void print(void) {
  int i;
  for(i = 0; i < sbufp; i++)
    printf("%g ", sbuf[i]);
}

void clear(void) {
  sbufp = 0;
}
