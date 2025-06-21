#include <stdio.h>
#include "util.h"

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
}
