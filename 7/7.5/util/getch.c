#include <stdio.h>
#include "util.h"

int getch(char *src) {
  static char *srcptr = NULL;
  static char *prevreadptr = NULL;
  static int isfinish = 0;

  if(src == NULL || *src == '\0') {
    /* reset */
    srcptr = NULL;
    prevreadptr = NULL;
    isfinish = 0;
    /* reset */

    if(src == NULL)
      return getchar();
    else
      return EOF;
  }

  /* this prevents reads of an exhausted string memory,
    to allow safe free of it in caller side.
  */
  if(isfinish)
    return EOF;

  if(srcptr != src)
    prevreadptr = srcptr = src;

  if(*prevreadptr != '\0')
    return *prevreadptr++;

  srcptr = NULL;
  prevreadptr = NULL;
  isfinish = 1;

  return EOF;
}

/* invalid implementation:
because of statically stored pointer from outside,
this implementation is error prone - if pointer
is invalidated (e.g. freed) by caller, any usage
including comparison of it will lead to undefined
behaviour as defined by standard.

code:
int getch(char *src) {
  static char *srcptr = NULL;
  static char *prevreadptr = NULL;
  if(srcptr != src)
    prevreadptr = srcptr = src;

  if(src == NULL)
    return getchar();

  if(*prevreadptr != '\0')
    return *prevreadptr++;

  return EOF;
} */
