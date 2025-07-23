/* we introduced line columns, and clip string.
  we will have separate function for each
  specific column type to be flexable.
  so we will have pagecol, titlecol and so on.

  linesize, columnsize are predefined.

  column will try to fit anything it gets,
  trimming rest part with ellipsis.
*/

#include <stdio.h>
#include <stdlib.h>
#include "pageprops.h"

#if LINESIZE < 2 * COLSIZE
  #error line should be able to contain title, page columns.
#endif

#if PAGESIZE <= 0
  #error page size must be positive integer
#endif

char pageline[LINESIZE + 1];

#define fillline(c) do {\
  int i;\
  for(i = 0; i < LINESIZE; i++)\
    /* doc: not using putc with stdout because possibly more than one evalation
      of a stream could happen. (alternatively can use fputc)
    */\
    putchar((c));\
} while(0);

void printheader(char *title, int page);

main(int argc, char *argv[]) {
  FILE *fp;
  int npage, nline, linelen;
  char *prog = argc > 0 ? *argv : "unnamed prog";

  if(argc <= 1) {
    fprintf(stderr, "%s error: %s.\n", prog, "should provide at least one file argument");
    exit(1);
  }

  while(*++argv) {
    if((fp = fopen(*argv, "r")) == NULL) {
      fprintf(stderr, "%s error: %s %s.\n", prog, "unable to open a file", *argv);
      continue;
    }

    /* doc: first page could be empty (even though ANSI C
      define "zero length file" as implementation defined)
    */
    npage = 1;
    nline = 0;

    while(fgets(pageline, LINESIZE, fp) != NULL) {
      if(nline == PAGESIZE)
        npage++;

      if((nline = (nline + 1) % PAGESIZE) == 1)
        printheader(*argv, npage);
      else if(nline == 0)
        nline = PAGESIZE;

      linelen = printf("%s", pageline);
      if(pageline[linelen - 1] != '\n')
          putchar('\n');
    }

    if(ferror(fp))
      fprintf(stderr, "%s error: %s %s.\n", prog, "can\'t read file", *argv);
    else if(nline == 0)
      fprintf(stderr, "%s: %s %s.\n", prog, "zero length file", *argv);
    fclose(fp);
  }

  return 0;
}

#include <stdio.h>
#include "column/column.h"

static char col[COLSIZE];

void printheader(char *title, int page) {
  fillline('-');
  putchar('\n');
  printf("%s", sprinttitlecol(col, title));
  printf("%s", sprintpagecol(col, page));
  putchar('\n');
  fillline('-');
  putchar('\n');
}
