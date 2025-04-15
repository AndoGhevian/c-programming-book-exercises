#ifndef WORDTYPE_H
#define WORDTYPE_H

enum {
  STRING_LITERAL = -1000,
  COMMENT,
  CONTROL_PREPROCESSOR,
  PREPROCESSOR,
  TOKEN,
  UNKNOWN
};

#define MAXTYPEWORD 1000
int getwordtype(void);

#endif
