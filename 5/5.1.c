#include <stdio.h>
#include <ctype.h>
#include "../utils/char_utils.h"

enum InputSignal {
  END_OF_FILE = EOF,
  NUMBER = 0,
  NOT_A_NUMBER,
};

enum InputSignal getint(int *pn);

main() {
  int x, s;

  while((s = getint(&x)) != EOF)
    if(s == NUMBER)
      printf("signal: %d parsed number: %d\n", s, x);
    else
      printf("signal: %d parsed symbol: %c\n", s, x);

  return 0;
}

enum InputSignal getint(int *pn) {
  int c, signch;

  while(isspace(c = getch()));

  if(c != '-' && c != '+' && !isdigit(c)) {
    *pn = c;
    return c == EOF ? END_OF_FILE : NOT_A_NUMBER;
  }

  signch = '+';
  if(c == '-' || c == '+') {
    signch = c;
    c = getch();

    if(!isdigit(c)) {
      *pn = signch;
      ungetch(c);
      return NOT_A_NUMBER;
    }
  }

  *pn = 0;
  do
    *pn = *pn * 10 + c - '0';
  while(isdigit(c = getch()));
  ungetch(c);

  *pn = signch == '+' ? *pn : -*pn;
  return NUMBER;
}
