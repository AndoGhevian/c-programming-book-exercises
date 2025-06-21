#include <string.h>
#include <ctype.h>
#include "util.h"

enum optypes getop(char *s, int *oplen) {
  int i;
  char **abbrptr;
  int *abbrlenptr;
  
  *oplen = 0;
  if(isdigit(*s))
    return NUMPUSH;
  if(*s == '&')
    return VAR;

  for(i = 0; i < N_OPABBRS; i++)
    for(abbrptr = opabbrs[i].abbr, abbrlenptr = opabbrs[i].abbrlen;
      *abbrptr != NULL;
      abbrptr++, abbrlenptr++
    )
      if(strncmp(s, *abbrptr, *abbrlenptr) == 0) {
        *oplen = *abbrlenptr;
        return opabbrs[i].type;
      }
  return UNKNOWN_OP;
}
