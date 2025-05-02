/*solution considerations:
  preprocessor's code scanning is
  ended up in a loop with steps (this is casual definition):
  Read input and perform this actions on tokens:
    1. if no directive, search encountered token in symbol table:
      1. if found peform following steps on replacement text:
        1. perform all concatenations of tokens adjacent to ##(token-pasting operator).
        2. replace symbolic names with appropriate replacement texts.
        3. rescan if one of the previous steps occure.
      2. if token was in symbol table replace it by result of a previous step.
      3. if token was not in symbol table add token.
    2. if define directive encountered, register/redefine
      symbolic name, replacement text pair in table.
    3. if undef directive encounter, remove symbolic name from table.

  comments inside the code text must be omitted.
  tokens inside strings, characters are not replaced.
  (including comments and strings inside replacement text)
*/

#include <stdio.h>
#include <ctype.h>
#include "tokenizer.h"
#include "symbols.h"
#include "char.h"

struct codeblock;

struct codeblock *addcode(struct codeblock *, char *);
struct codeblock *addprocesscode(struct codeblock *, char *);
void printcode(struct codeblock *);

int getdirective(void);

#define MAXTOKEN 1000
char token[MAXTOKEN];

#define MAXREPLTXT 10000
char symbolicname[MAXTOKEN];
char replacetxt[MAXREPLTXT];
char *replacetxtptr = replacetxt;

main() {
  int c, ttype, lim, isesc;
  struct codeblock *codelist = NULL;

  while((c = getch(NULL)) != EOF)
    if(c == '#')
      switch(getdirective()) {
        case DEFINE:
          if(getsymbolicname(symbolicname, MAXTOKEN))
            break;

          while(isblank(c = getch(NULL)));
          ungetch(c, NULL);

          isesc = 0;
          lim = MAXREPLTXT;
          replacetxtptr = replacetxt;
          while(--lim && (c = getch(NULL)) != EOF && (c != '\n' || isesc))
            switch(c) {
              case '\n':
                /* (replacetxtptr - 1) is a valid pointer because
                  at this point previous character must be '\' */
                *(replacetxtptr - 1) = ' ';
                isesc = 0;
                break;
              case '\\':
                isesc = 1;
                /* intentional no-break */
              default:
                *replacetxtptr++ = c;
                break;
            }
          *replacetxtptr = '\0';
          if(c != EOF)
            install(symbolicname, replacetxt);
          break;
        case UNDEF:
          if(getsymbolicname(symbolicname, MAXTOKEN))
            break;
          uninstall(symbolicname);
          break;
        default:
          break;
      }
    else {
      ungetch(c, NULL);
      if(getspace(token, MAXTOKEN, NULL))
        codelist = addcode(codelist, token);
      else
        switch(gettoken(token, MAXTOKEN, NULL)) {
          case COMMENT:
          case EOF:
            break;
          case NAME:
            codelist = addprocesscode(codelist, token);
            break;
          case STRING:
          case NUMBER:
          default:
            codelist = addcode(codelist, token);
            break;
        }
    }

  printcode(codelist);
  return 0;
}

#include <stdio.h>
#include "keyval.h"
#include "tokenizer.h"

#define DIRNOTFOUND EOF - 1

/* inc sorted on key */
struct keyval directives[] = {
  "define", DEFINE,
  "endif", DIRNOTFOUND,
  "if", DIRNOTFOUND,
  "undef", UNDEF
};

#define NDIR sizeof directives / sizeof directives[0]

char dirstr[MAXTOKEN];

int getdirective(void) {
  struct keyval *directive = NULL;

  if(gettoken(dirstr, MAXTOKEN, NULL) == EOF)
    return EOF;

  if(directive = binsrch_keyval(dirstr, directives, NDIR))
    return directive->value;
  return DIRNOTFOUND;
}

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "char.h"

struct codeblock {
  struct codeblock *next;
  char *token;
};

struct codeblock *addcode(struct codeblock *, char *);

char proctoken[MAXTOKEN];

struct codeblock *addprocesscode(struct codeblock *codelist, char *code) {
  int c, ttype;
  struct nlist *symbol;

  while((c = getch(code)) != EOF) {
    ungetch(c, code);
    if(getspace(proctoken, MAXTOKEN, code))
      codelist = addcode(codelist, proctoken);
    else
      switch(gettoken(proctoken, MAXTOKEN, code)) {
        case NAME:
          if(symbol = lookup(proctoken))
            codelist = addprocesscode(codelist, symbol->defn);
          else
            codelist = addcode(codelist, proctoken);
          break;
        case COMMENT:
          break;
        case STRING:
        case NUMBER:
        default:
          codelist = addcode(codelist, proctoken);
          break;
      }
  }

  return codelist;
}

void printcode(struct codeblock *codelist) {
  if(codelist == NULL)
    return;

  if(codelist->next)
    printcode(codelist->next);
  printf("%s", codelist->token);
}

#include <string.h>

static char *l_strdup(char *);

struct codeblock *addcode(struct codeblock *codelist, char *code) {
  struct codeblock *cblock = (struct codeblock *)malloc(sizeof(struct codeblock));
  if(cblock) {
    if(cblock->token = l_strdup(code)) {
      strcpy(cblock->token, code);
      cblock->next = codelist;
      return cblock;
    } else
      free(cblock);
  }

  return codelist;
}

static char *l_strdup(char *s) {
  char *cpy;

  if((cpy = (char *)malloc(strlen(s) + 1)) == NULL)
    return NULL;
  strcpy(cpy, s);
  return cpy;
}
