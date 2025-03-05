#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"

extern int len;
extern char line[];
void get_line(void);

int i;
int getop(char s[]) {
  int li;

  if(!len || i == len) {
    i = 0;
    get_line();
  }

  while(isspace(s[0] = line[i++]) && s[0] != '\n');
  s[1] = '\0';

  li = 0;
  if(isalpha(s[0]))
    while(isalpha(s[++li] = line[i]))
      i++;
  else {
    if(s[0] == '-' || s[0] == '+' || isdigit(s[0]))
      while(isdigit(s[++li] = line[i]))
        i++;

    if(s[li] == '.')
      while(isdigit(s[++li] = line[++i]));
  }

  if(li != 0)
    s[li] = '\0';

  if(s[0] == '\0')
    return EOF;

  if(isdigit(s[0]))
    return NUMBER;

  if(li == 0 || li == 1) {
    if(isalpha(s[0]))
      return VAR;
    return s[0];
  }

  if(!isalpha(s[0]))
    return NUMBER;

  if(!strcmp(s, "prnt") || !strcmp(s, "print"))
    return PRINT;
  if(!strcmp(s, "dup") || !strcmp(s, "duplicate"))
    return DUPLICATE;
  if(!strcmp(s, "sw") || !strcmp(s, "swp") || !strcmp(s, "swap"))
    return SWAP;
  if(!strcmp(s, "clr") || !strcmp(s, "clear"))
    return CLEAR;
  if(!strcmp(s, "sin"))
    return SIN;
  if(!strcmp(s, "exp"))
    return EXP;
  if(!strcmp(s, "pow"))
    return POW;
}

#define LINELIMIT 100

int len;
char line[LINELIMIT + 1];

void get_line(void) {
  int c, i;
  int lim = LINELIMIT;

  i = 0;
  while(--lim >= 0 && (c = getchar()) != EOF && c != '\n')
    line[i++] = c;
  if(c == '\n')
    line[i++] = c;

  line[i] = '\0';
  len = i;
}
