#include <stdio.h>
#include "charbuf.h"

static char chstore[MAXCHSTORE];
static char *chptr = chstore;

int getch(void) {
  if(chptr > chstore)
    return *--chptr;
  return getchar();
}

void ungetstr(char *str) {
  char *s = str;
  while(*s)
    s++;

  while(s > str && chptr < chstore + MAXCHSTORE)
    *chptr++ = *--s;

  if(chptr == chstore + MAXCHSTORE)
    printf("no enough space to unget part of a string");
}

void ungetch(char c) {
  if(chptr == chstore + MAXCHSTORE) {
    printf("no enough space to unget character");
    return;
  }

  *chptr++ = c;
}
