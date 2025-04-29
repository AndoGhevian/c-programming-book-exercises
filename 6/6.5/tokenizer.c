#include <stdio.h>
#include <ctype.h>
#include "tokenizer.h"
#include "../../utils/char_utils.h"

int getsymbolicname(char *name, int lim) {
  int c, ttype;
  while(isblank(c = getch()));
  if(c == '\n') {
    printf("expected an identifier\n");
    return 1;
  }
  ungetch(c);

  while((ttype = gettoken(name, lim)) == COMMENT);
  if(ttype == EOF)
    return EOF;
  if(ttype != NAME) {
    printf("expected an identifier\n");
    return 1;
  }

  return 0;
}
