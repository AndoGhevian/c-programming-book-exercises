#include <stdio.h>

static int sch = EOF;

int getch(void) {
  int msch;

  return msch = sch, msch != EOF ? sch = EOF, msch : getchar();
}

void ungetch(int c) {
  sch = c; 
}
