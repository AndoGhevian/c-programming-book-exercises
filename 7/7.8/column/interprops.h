#ifndef COL_INTERPROPS_H
#define COL_INTERPROPS_H
/* internal for each printcol */
#define MAXFMT 1000
static char printfmt[MAXFMT];
/*_________________________*/

#define fillellipsis(s, n) do {\
  int i;\
  for(i = 0; i < (n); i++) (s)[i] = '.';\
} while(0);
#endif
