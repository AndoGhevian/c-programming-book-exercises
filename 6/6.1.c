#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "../utils/alloc.h"

enum {
  STRING_LITERAL = -1000,
  COMMENT,
  PREPROCESSOR
};

/* tables must be sorted in increasing order to apply binary search */
struct key {
  char *keyword;
  int count;
} keytab[] = {
  {"_synthetic_keyword"}, /* I think count will default to 0 as for an external array element initializer */
  "break", 0,
  "const", 0,
  "while", 0,
};

#define MAXCODELINES 100
struct code {
  char *type;
  char *lineptr[MAXCODELINES];
  int count;
} codetab[] = {
  {"comment"},
  {"preprocessor"},
  {"string"},
/* if we want to combine this table with keywords table,
    we can also use symbols, to make them not to conflict with each other:
 */
/*   "\"", 0,
  {"/", 0,},
  "#", 0, */
};

#define NKEYS sizeof keytab / sizeof(struct key)
#define NCODE sizeof codetab / sizeof(struct code)

/* returns negative values
    for special code structures like comment,
    string literal.
  See enum.
 */
int getword(char *, int);

/* 2 binsearch implementations needed */
int binsrch_key(char *, struct key[], int);
int binsrch_code(char *, struct code[], int);

#define MAXWORD 100
main() {
  int i;
  char c, word[MAXWORD], *code;

  while((c = getword(word, MAXWORD)) != EOF)
    if(c == '_' || isalpha(c)) {
      if((i = binsrch_key(word, keytab, NKEYS)) >= 0)
        keytab[i].count++;
    } else {
      switch(c) {
        case STRING_LITERAL:
          i = binsrhc_code("string", codetab, NCODE);
          break;
        case COMMENT:
          i = binsrhc_code("comment", codetab, NCODE);
          break;
        case PREPROCESSOR:
          i = binsrch_code("preprocessor", codetab, NCODE);
          break;
        default:
          i = -1;
          break;
      }
      if(i < 0)
        continue;

      code = alloc(strlen(word));
      if(++codetab[i].count <= MAXCODELINES && code)
        codetab[i].lineptr[codetab[i].count - 1] = strcpy(code, word);
    }
}

int getword(char *word, int lim) {
  /* Working on implementation... */
}

int binsrhc_key(char *key, struct key tab[], int lim) {
  int cond;
  int low, high, mid;

  low = 0;
  high = lim - 1;
  while(high >= low)
    if((cond = strcmp(key, tab[mid = (high + low) / 2].keyword)) < 0)
      high = mid - 1;
    else if(cond > 0)
      low = mid + 1;
    else
      return mid;
  return -1;
}

int binsrhc_code(char *type, struct code tab[], int lim) {
  int cond;
  int low, high, mid;

  low = 0;
  high = lim - 1;
  while(high >= low)
    if((cond = strcmp(type, tab[mid = (high + low) / 2].type)) < 0)
      high = mid - 1;
    else if(cond > 0)
      low = mid + 1;
    else
      return mid;
  return -1;
}
