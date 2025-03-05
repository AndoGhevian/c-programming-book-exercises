
#include <stdio.h>
#include <string.h>
#include "calc.h"
#define CHBUFFSIZE 100

int sch = EOF;

int getch(void) {
  int msch;

  return msch = sch, msch != EOF ? sch = EOF, msch : getchar();
}

void ungetch(int c) {
  sch = c; 
}

char cbuf[CHBUFFSIZE];
int cbufp = 0;

int getch_many(void) {
  return (cbufp > 0) ? cbuf[--cbufp] : getchar();
}

void ungetch_many(int c) {
  if(cbufp >= CHBUFFSIZE)
    printf("ungetch: too many characters\n");
  else
    cbuf[cbufp++] = c;
}

void ungets(char s[]) {
  int i;

  for(i = strlen(s) - 1; i >= 0; i--)
    ungetch_many(s[i]);
}
