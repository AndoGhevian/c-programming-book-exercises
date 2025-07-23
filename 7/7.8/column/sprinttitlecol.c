#include <stdio.h>
#include "../pageprops.h"
#include "../strclip.h"
#include "column.h"
#include "interprops.h"

/* this solution is an extendable boilerplate for fitting any
  multipart content inside any sized column, given column can
  at least contain clipper string.
  note: column expansion affects only last part of the content,
    others must be appropriately sized before full column truncation.
  warning: current solution of column trimming can result in
  extra ellipsis.
*/
char *sprinttitlecol(char *col, char *title) {
  int i, clippedsize;

  if((clippedsize = strclip(title, 0, CLIPSIZE, COLSIZE - CLIPSIZE)) != 0)
    fillellipsis(col, CLIPSIZE);

  if(clippedsize)
    sprintf(col + CLIPSIZE, "%s", title + clippedsize);
  else
    sprintf(col, "%*s", COLSIZE, title);
  return col;
}
