/* we introduced line columns, and clip string.
  we will have separate function for each
  specific column type to be flexable.
  so we will have pagecol, titlecol and so on.

  linesize, columnsize are predefined.

  column will try to fit anything it gets,
  trimming rest part with ellipsis.
*/

#include <stdio.h>
#include "pageprops.h"
#include "column/col.h"

main() {
  char col[COLSIZE + 1];

  printpagecol(col, 1000000);

  printf("%s\n", col);

  return 0;
}
