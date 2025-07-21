/* we introduced line columns, and clip string.
  we will have separate function for each
  specific column type to be flexable.
  so we will have pagecol, titlecol and so on.

  linesize, columnsize are predefined.

  column will try to fit anything it gets,
  trimming rest part with ellipsis.
*/

#include <stdio.h>
#include "strclip.h"
#include "pageprops.h"

/* col cliped by ellipsis ...
  you can set 0 to hide ellipsis.
*/
#define CLIPSIZE 3

#if CLIPSIZE > COLSIZE
  #error clip size should be less than or equal to column size.
#endif

void pagecol(unsigned int page, char *col);

main() {
  char col[COLSIZE + 1];

  pagecol(1000000, col);

  printf("%s\n", col);

  return 0;
}

/* reusable through col fitters */
#define MAXFMT 1000
char printfmt[MAXFMT];
/*_________________________*/

#define fillellipsis(s, n) do {\
  int i;\
  for(i = 0; i < (n); i++) (s)[i] = '.';\
} while(0);

#define MAX_INT_DIG 100
char numstr[MAX_INT_DIG];

/* there is possibility to implement more sophisticated
  solution, but in the end the provided one is enough.
*/

/* this solution is an extendable boilerplate for fitting any
  multipart content inside any sized column, given column can
  at least contain clipper string.
  note: column expansion affects only last part of the content,
    others must be appropriately sized before full column truncation.
  warning: current solution of column trimming can result in
  extra ellipsis.
*/
void pagecol(unsigned int page, char *col) {
  static char const label[] = "page ";
  static int const labelen = (sizeof label) - 1;
  static int const pageclip_skip = 1;
  static int const pageclip_rest = 2;

  int i, clippedsize, notfit;
  int numlen, fmtlen, outboundlen;

  /* separate column truncation common mechanism*/
  /*______________________________________________________*/
  numlen = sprintf(numstr, "%u", page);
  if((outboundlen = labelen + numlen - COLSIZE) > 0) {
    if((clippedsize = strclip(numstr, pageclip_skip, CLIPSIZE, pageclip_rest)) != 0) {
      fillellipsis(numstr + pageclip_skip, CLIPSIZE);
      /* strcpy is not safe: overlapping mem regions */
      for(i = 0; i < pageclip_rest; i++)
        numstr[pageclip_skip + CLIPSIZE + i] = numstr[pageclip_skip + clippedsize + i];
      numstr[pageclip_skip + CLIPSIZE + pageclip_rest] = '\0';
    }
    numlen = numlen - clippedsize + CLIPSIZE;
  }
  /*______________________________________________________*/


  /* (final step) full column truncation solution with minimal memory usage */
  /* and without extra memory copy. */
  /* you can do this in much more simpler way if use intermediate */
  /* temporary character array, which we do not do here. */
  /*    */
  /*______________________________________________________*/
  /* make sure to understand pattern of multipart column trimming */
  /* provided in the code below. */
  /*______________________________________________________*/
  if((outboundlen = labelen + numlen - COLSIZE) > 0) {
    if(outboundlen + CLIPSIZE <= numlen)
      fmtlen = sprintf(printfmt, "%%-s" "%%+%d.%ds", COLSIZE - CLIPSIZE - labelen, numlen - (outboundlen + CLIPSIZE));
    else if(outboundlen + CLIPSIZE <= numlen + labelen)
      /* note: this format contains extra part to preserve boierplate pattern,
          its minimal width part make sense only if right adjacement is used
          for a label. simplified fmt is "%%.%ds".
      */
      fmtlen = sprintf(printfmt, "%%-%d.%ds", COLSIZE - CLIPSIZE, numlen + labelen - (outboundlen + CLIPSIZE));
    else
      fmtlen = sprintf(printfmt, "%s", "");
    fillellipsis(printfmt + fmtlen, CLIPSIZE);
  }
  else
    sprintf(printfmt, "%%-s" "%%+%ds", COLSIZE - labelen);
  /*______________________________________________________*/

  sprintf(col, printfmt, label, numstr);
}

/* here other col fitters */
