#include <stdio.h>

static int sch = EOF;

int getch(void) {
  int msch;

  return msch = sch, msch != EOF ? sch = EOF, msch : getchar();
}

void ungetch(int c) {
  sch = c; 
}

#define CHBUFFSIZE 100
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
