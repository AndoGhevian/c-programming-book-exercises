#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "../utils/alloc.h"

enum {
  STRING_LITERAL = -1000,
  COMMENT,
  CONTROL_PREPROCESSOR,
  PREPROCESSOR,
  TOKEN,
  UNKNOWN
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

      code = alloc(strlen(word));
      if(++codetab[i].count <= MAXCODELINES && code)
        codetab[i].lineptr[codetab[i].count - 1] = strcpy(code, word);
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

int getch(void);
void ungetch(char c);
void ungetstr(char *str);

/* see enum for types */
int getwordtype(void);

/*
  this handles also multiline comments and preprocessors.
  we assume there is NO "null characters" inside input.
*/
int getword(char *word, int lim) {
  char *w, *ends;
  int endlen, isnw, isesc, c, type;
  while(isspace(c = getch()));
  if(c == EOF)
    return EOF;
  ungetch(c);

  isnw = 0;
  w = word;
  switch(type = getwordtype()) {
    case TOKEN:
      while(--lim > 0 && isalnum(c = getch()))
        *w++ = c;
      *w = '\0';

      if(lim)
        ungetch(c);
      isnw = 1;
      break;
    case COMMENT:
      ends = "*/";
      endlen = strlen(ends);
      while(--lim > 0 && (c = getch()) != EOF) {
        *w++ = c;
        if(w - word >= endlen)
          if(isnw = strncmp(w - endlen, ends, endlen))
            break;
      }
      *w = '\0';
      break;
    case CONTROL_PREPROCESSOR:
      ends = "#endif";
      endlen = strlen(ends);
      while(--lim > 0 && (c = getch()) != EOF) {
        *w++ = c;
        if(w - word >= endlen)
          if(isnw = strncmp(w - endlen, ends, endlen))
            break;
      }
      *w = '\0';

      /* check only space after end */
      if(isnw && (c = getch()) != EOF)
        isnw = isspace(c), ungetch(c);

      /* check only space before end */
      if(isnw && w - word > endlen)
        isnw = isspace(*(w - endlen - 1));

      break;
    case PREPROCESSOR:
      isesc = 0;
      while(--lim > 0 && (c = getch()) != EOF) {
        *w++ = c;
        if(isnw = c == '\n' && !isesc)
          break;
        if(c == '\\')
          isesc = isesc ? 0 : 1;
        else
          isesc = 0;
      }
      *w = '\0';
      break;
    case STRING_LITERAL:
      isesc = 0;
      while(--lim > 0 && (c = getch()) != EOF && c != '\n') {
        *w++ = c;
        /* make sure it is not an opening quote '"' */
        if(w - word > 1)
          if(isnw = c == '\"' && !isesc)
            break;
        if(c == '\\')
          isesc = isesc ? 0 : 1;
        else
          isesc = 0;
      }
      *w = '\0';
      break;
    case UNKNOWN:
      if(--lim && (c = getch()) != EOF)
        *w++ = c;
      *w = '\0';
      isnw = 1;
      break;
  }

  if(!isnw)
    return UNKNOWN;
  return type;
}

struct {char *typeword; int type;} typetab[] = {
  "\"", STRING_LITERAL,
  "/*", COMMENT,
  "#if", CONTROL_PREPROCESSOR,
  "#ifdef", CONTROL_PREPROCESSOR,
  "#ifndef", CONTROL_PREPROCESSOR,
  "#define", PREPROCESSOR,
};
#define NTYPEWORD sizeof typetab

#define MAXTYPEWORD 1000
int getwordtype(void) {
  char *typeword[NTYPEWORD], word[MAXTYPEWORD], *w = word;
  int i, nt;

  for(i = 0; i < NTYPEWORD; i++)
    typeword[i] = typetab[i].typeword;

  nt = NTYPEWORD;
  while(w - word < MAXTYPEWORD - 1 && nt && (*w++ = getch()) != EOF)
    for(i = 0; i < NTYPEWORD; i++)
      if(typeword[i])
        if(*typeword[i] == '\0') {
            /* check preprocessors end with space */
            if(!strcmp(typetab[i].typeword, "#if")
            || !strcmp(typetab[i].typeword, "#ifdef")
            || !strcmp(typetab[i].typeword, "#ifndef")
            || !strcmp(typetab[i].typeword, "#define")
          )
            if(!isspace(*w)) {
              typeword[i] = NULL;
              nt--;
              continue;
            }

          *w++ = '\0';
          ungetstr(word);
          return typetab[i].type;
        } else if(*typeword[i]++ != *w) {
          typeword[i] = NULL;
          nt--;
        }
  *w++ = '\0';
  ungetstr(word);
  if(isalpha(*word) || *word == '_')
    return TOKEN;
  return UNKNOWN;
}

#define MAXCHSTORE 1000
char chstore[MAXCHSTORE];
char *chptr = chstore;

int getch(void) {
  if(chptr > chstore)
    return *--chptr;
  return getchar();
}

void ungetstr(char *str) {
  char *s = str;
  while(*s)
    s++;

  while(s > str && chptr < chstore + MAXCHSTORE)
    *chptr++ = *--s;

  if(chptr == chstore + MAXCHSTORE)
    printf("no enough space to unget part of a string");
}

void ungetch(char c) {
  if(chptr == chstore + MAXCHSTORE) {
    printf("no enough space to unget character");
    return;
  }

  *chptr++ = c;
}
