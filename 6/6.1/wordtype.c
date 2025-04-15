#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "charbuf.h"
#include "wordtype.h"

struct {char *typeword; int type;} typetab[] = {
  "\"", STRING_LITERAL,
  "/*", COMMENT,
  "#if", CONTROL_PREPROCESSOR,
  "#ifdef", CONTROL_PREPROCESSOR,
  "#ifndef", CONTROL_PREPROCESSOR,
  "#define", PREPROCESSOR,
};
#define NTYPEWORD sizeof typetab

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
