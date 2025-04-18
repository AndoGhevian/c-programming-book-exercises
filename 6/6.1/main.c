#include <stdio.h>
#include <string.h>
#include "word.h"
#include "../../utils/alloc.h"

/* tables must be sorted in increasing order to apply binary search */
static struct key {
  char *keyword;
  int count;
} keytab[] = {
  {"_synthetic_keyword"}, /* I think count will default to 0 as for an external array element initializer */
  "break", 0,
  "const", 0,
  "while", 0,
};

#define MAXCODELINES 100
static struct code {
  char *typeword;
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

/* returns negative enumeration constant values
    for special code structures like comment,
    string literal.
  see enum.
 */
int getword(char *, int);

/* 2 binsearch implementations needed */
int binsrch_key(char *, struct key[], int);
int binsrch_code(char *, struct code[], int);

void writelines(char **, int);

#define MAXWORD 100
main() {
  int i, t;
  char word[MAXWORD], *code;

  while((t = getword(word, MAXWORD)) != EOF)
    if(t == TOKEN) {
      if((i = binsrch_key(word, keytab, NKEYS)) >= 0)
        keytab[i].count++;
    } else {
      switch(t) {
        case STRING_LITERAL:
          i = binsrch_code("string", codetab, NCODE);
          break;
        case COMMENT:
          i = binsrch_code("comment", codetab, NCODE);
          break;
        case CONTROL_PREPROCESSOR:
        case PREPROCESSOR:
          i = binsrch_code("preprocessor", codetab, NCODE);
          break;
        case UNKNOWN:
        default:
          i = -1;
          break;
      }
      if(i < 0)
        continue;

      code = alloc(strlen(word) + 1);
      if(++codetab[i].count <= MAXCODELINES && code)
        codetab[i].lineptr[codetab[i].count - 1] = strcpy(code, word);
    }

  printf("\nkeywords found\n\n");
  for(i = 0; i < NKEYS; i++)
    printf("keyword: %s, count: %d\n", keytab[i].keyword, keytab[i].count);

  printf("\ncode structures found\n\n");
  for(i = 0; i < NCODE; i++) {
    printf("code structure %s, count: %d\n", codetab[i].typeword, codetab[i].count);
    writelines(codetab[i].lineptr, MAXCODELINES);
  }
}

int binsrch_key(char *key, struct key tab[], int lim) {
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

int binsrch_code(char *type, struct code tab[], int lim) {
  int cond;
  int low, high, mid;

  low = 0;
  high = lim - 1;
  while(high >= low)
    if((cond = strcmp(type, tab[mid = (high + low) / 2].typeword)) < 0)
      high = mid - 1;
    else if(cond > 0)
      low = mid + 1;
    else
      return mid;
  return -1;
}

void writelines(char **lineptr, int maxlines) {
  while(maxlines-- > 0 && *lineptr)
    printf("%s\n", *lineptr++);
}
