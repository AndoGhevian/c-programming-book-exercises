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

/* returns space count (including newlines) or EOF */
int getspace(char *, int);

/* read next token, skips space characters (including newline).
  returns supported token type, encountered character or EOF.
  note: limit of character storage must be at least 4 (for comments),
  in case if no end of comment or string reached, it will early close
  to not lose any input */
int gettoken(char *, int);

/* 1 if invalid, 0 if valid symbol identifier or EOF */
int getsymbolicname(char *, int);

#endif
