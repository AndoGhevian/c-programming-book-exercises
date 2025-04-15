#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "charbuf.h"
#include "wordtype.h"

static struct {char *typeword; int type;} typetab[] = {
  "\"", STRING_LITERAL,
  "/*", COMMENT,
  "#if", CONTROL_PREPROCESSOR,
  "#ifdef", CONTROL_PREPROCESSOR,
  "#ifndef", CONTROL_PREPROCESSOR,
  "#define", PREPROCESSOR,
};
#define NTYPEWORD sizeof typetab / sizeof typetab[0]

int getwordtype(void) {
  char *typeword[NTYPEWORD], word[MAXTYPEWORD], *w = word;
  int i, nt, found;

  for(i = 0; i < NTYPEWORD; i++)
    typeword[i] = typetab[i].typeword;

  found = 0;
  nt = NTYPEWORD;
  for(;!found && w - word < MAXTYPEWORD - 1 && nt && (*w = getch()) != EOF; w++)
    for(i = 0; i < NTYPEWORD; i++)
      if(typeword[i])
        if(*typeword[i] == '\0') {
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

          found = 1;
          break;
        } else if(*typeword[i]++ != *w) {
          typeword[i] = NULL;
          nt--;
        }

  *w = '\0';
  ungetstr(word);
  if(found)
    return typetab[i].type;

  if(isalpha(*word) || *word == '_')
    return TOKEN;
  return UNKNOWN;
}
