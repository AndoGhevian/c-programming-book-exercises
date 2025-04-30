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
#include "../../utils/char_utils.h"

struct nlist;
struct codeblock;

struct nlist *lookup(char *);
struct nlist *install(char *, char *);
struct nlist *uninstall(char *);

struct codeblock *addcodetok(struct codeblock *, char *);
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
  struct codeblock *codetext;

  while((c = getch()) != EOF)
    if(c == '#')
      switch(getdirective()) {
        case DEFINE:
          if(getsymbolicname(symbolicname, MAXTOKEN))
            break;

          while(isblank(c = getch()));
          ungetch(c);

          isesc = 0;
          lim = MAXREPLTXT;
          replacetxtptr = replacetxt;
          while(--lim && (c = getch()) != EOF && (c != '\n' || isesc))
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
      ungetch(c);
      if(getspace(token, MAXTOKEN) > 0)
        codetext = addcodetok(codetext, token);
      switch(gettoken(token, MAXTOKEN)) {
        case COMMENT:
        case EOF:
          break;
        case NAME:
        case STRING:
        case NUMBER:
        default:
          codetext = addcodetok(codetext, token);
          break;
      }
    }

  printcode(codetext);
  return 0;
}

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

struct codeblock {
  struct codeblock *next;
  char *token;
};

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
  int i;
  struct keyval *directive = NULL;

  if(gettoken(dirstr, NDIR) == EOF)
    return EOF;

  if(directive = binsrch_keyval(dirstr, directives, NDIR))
    return directive->value;
  return DIRNOTFOUND;
}
