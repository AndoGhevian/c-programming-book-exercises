#include <stdio.h>
#include <ctype.h>
#include "tokenizer.h"
#include "char.h"

int getspace(char *space, int lim, char *input) {
  int c, n;

  for(n = 0; --lim && isspace(c = getch(input)); n++)
    *space++ = c;
  *space = '\0';

  if(lim)
    ungetch(c, input);

  return n;
}

int gettoken(char *token, int lim, char *input) {
  int isa, isn, isc, iss;
  int c, endc;

  isa = isn = isc = iss = 0;

  while(isspace(c = getch(input)));
  if(c == EOF)
    return EOF;
  *token++ = c;

  endc = 0;
  if(c == '/')
    if(isc = (c = getch(input)) == '*') {
      for(
        *token++ = '*',
        lim -= 2,
        lim -= 2; /* to not to lost characters in case if no end of comment is reached */
        --lim && (c = getch(input)) != EOF && ((*token++ = c) != '/' || !endc);
        endc = c == '*'
      );
      if(!lim || c == EOF) {
        *token++ = '*';
        *token++ = '/';
      }
    }
    else
      ungetch(c, input), c = '/';
  else if(iss = c == '\"') {
    for(
      --lim,
      --lim; /* to not lost characters if no end of string reached */
      --lim && (c = getch(input)) != EOF && (*token++ = c) != '\"';
    );
    if(!lim || c == EOF)
      *token++ = '\"';
  }
  else if((isa = isalpha(c)) || (isn = isdigit(c)))
      for(--lim; --lim && isalnum(c = getch(input)); *token++ = c);

  *token = '\0';
  if(isa) {
    ungetch(c, input);
    return NAME;
  }

  if(isn) {
    ungetch(c, input);
    return NUMBER;
  }

  if(iss)
    return STRING;

  if(isc)
    return COMMENT;

  return *(token - 1);
}

int getsymbolicname(char *name, int lim) {
  int c, ttype;
  while(isblank(c = getch(NULL)));
  if(c == '\n') {
    printf("expected an identifier\n");
    return 1;
  }
  ungetch(c, NULL);

  while((ttype = gettoken(name, lim, NULL)) == COMMENT);
  if(ttype == EOF)
    return EOF;
  if(ttype != NAME) {
    printf("expected an identifier\n");
    return 1;
  }

  return 0;
}
