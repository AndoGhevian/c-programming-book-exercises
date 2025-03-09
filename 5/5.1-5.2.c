#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "../utils/char_utils.h"

enum NumberSignal {
  END_OF_FILE = EOF,
  NOT_A_NUMBER = 0,
  INT,
  FLOAT,
};

enum NumberSignal getint(int *pn);
enum NumberSignal getdouble(double *pn);

main() {
  double f;
  int x, s;

  while((s = getdouble(&f)) != EOF)
    if(s == FLOAT)
      printf("signal: %d parsed float: %g\n", s, f);
    else if(s == INT)
      printf("signal: %d parsed int: %g\n", s, f);
    else
      printf("signal: %d parsed symbol: %c\n", s, (int)f);

  return 0;
}

enum NumberSignal getdouble(double *pn) {
  int exp = 1, isfr = 0;
  int c, signch;

  while(isspace(c = getch_many()));

  if(c != '-' && c != '+' && c != '.' && !isdigit(c)) {
    *pn = c;
    return c == EOF ? END_OF_FILE : NOT_A_NUMBER;
  }

  signch = '\0';
  if(c == '-' || c == '+') {
    signch = c;
    c = getch_many();

    if(c != '.' && !isdigit(c)) {
      *pn = signch;
      ungetch_many(c);
      return NOT_A_NUMBER;
    }
  }

  if(c == '.') {
    isfr = 1;
    if(!isdigit(c = getch_many())) {
      if(signch) {
        ungetch_many(c);
        ungetch_many('.');
        *pn = signch;
      } else {
        *pn = '.';
        ungetch_many(c);
      }
      return NOT_A_NUMBER;
    }
  }

  *pn = 0;
  do {
    if(c != '.') {
      exp *= isfr ? 10 : 1;
      *pn = *pn * 10 + c - '0';
    }
  } while(isdigit(c = getch_many()) || (!isfr && (isfr = c == '.')));
  ungetch(c);

  *pn = (!signch || signch == '+' ? *pn : -*pn) / exp;
  if(isfr)
    return FLOAT;
  else
    return INT;
}

enum NumberSignal getint(int *pn) {
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
  return INT;
}
