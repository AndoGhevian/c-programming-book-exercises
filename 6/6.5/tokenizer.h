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

/* returns blanks count or EOF */
int getblank(char *, int);

/* read next token, skips space characters (including newline)
  returns supported token type, encountered character or EOF */
int gettoken(char *, int);

/* 1 if invalid, 0 if valid symbol identifier or EOF */
int getsymbolicname(char *, int);

#endif
