#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "charbuf.h"
#include "wordtype.h"
#include "word.h"

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
      while(--lim > 0 && isalnum(c = getch()) || c == '_')
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
          if(isnw = !strncmp(w - endlen, ends, endlen)) {
            break;
          }
      }
      *w = '\0';
      break;
    case CONTROL_PREPROCESSOR:
      ends = "#endif";
      endlen = strlen(ends);
      while(--lim > 0 && (c = getch()) != EOF) {
        *w++ = c;
        if(w - word >= endlen)
          if(isnw = !strncmp(w - endlen, ends, endlen))
            /* check only space after end */
            if((c = getch()) != EOF && !(isnw = isspace(c))) {
              ungetch(c);
              continue;
            }
            else
              break;
      }
      *w = '\0';

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
