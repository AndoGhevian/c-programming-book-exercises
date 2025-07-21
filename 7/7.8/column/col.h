#ifndef COL_H
#define COL_H
#include "../pageprops.h"

/* col cliped by ellipsis ...
  you can set 0 to hide ellipsis.
  flexible: there is no restriction
  to have private clipsize for each
  printcol.
*/
#define CLIPSIZE 3

#if CLIPSIZE > COLSIZE
  #error clip size should be less than or equal to column size.
#endif

void printpagecol(char *, unsigned int);
#endif
