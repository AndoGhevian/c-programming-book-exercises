#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
/* supported preprocessor directives */
enum {
  DEFINE,
  UNDEF
};

/* token types:
 make those not to interfere with EOF*/
enum {
  STRING = EOF - 1000,
  COMMENT,
  NAME,
  NUMBER,
};

/* returns space count (including newlines) or EOF
  (in case of non NULL input pointer EOF indicate
  null character). */
int getspace(char *, int, char *);

/* read next token from input
  (or standard input if input is NULL pointer),
  skips space characters (including newline).
  returns supported token type, encountered character or EOF
  (if input is not NULL pointer then EOF indicate null character).
  note: limit of character storage must be at least 4 (for comments),
  in case if no end of comment or string reached, it will early close
  to not lose any input. */
int gettoken(char *, int, char *);

/* 1 if invalid, 0 if valid symbol identifier or EOF */
int getsymbolicname(char *, int);

#endif
