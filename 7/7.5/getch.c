#include <stdio.h>
#include "util.h"

/* invalid implementation:
because of statically stored pointer from outside,
this implementation is error prone - if pointer
is invalidated (e.g. freed) by caller, any usage
including comparison of it will lead to undefined
behaviour as defined by standard.
*/
int getch(char *src) {
  static char *srcptr = NULL;
  static char *prevreadptr = NULL;
  if(srcptr != src) /* leads to error */
    prevreadptr = srcptr = src;

  if(src == NULL)
    return getchar();

  if(*prevreadptr != '\0')
    return *prevreadptr++;

  return EOF;
}
