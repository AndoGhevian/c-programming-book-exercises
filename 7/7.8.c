/* we introduced line columns, and clip string.

  but defining column clip, start, end strings
  using symbolic names introduces difficulties
  for reusable function implementations.

  first of all, we need to ensure that clip string
  can be contained by column, which size we provide
  by separate symbolic name.
  this check is not intended to be done at runtime,
  but rather need to be guaranteed while coding,
  otherwise it is logical error.

  if we decide to always use ellipsis for text clip
  and specifiy the number of that dots as a symbolic
  name, rather than clip string, then we can use it
  in preprocessor condition to show error for invalid
  clip size.

  for start and end parts, it is not possible to
  specify only numbers, because they can be arbitrary
  strings, so they will be provided as arguments
  and check will be done at runtime.
*/

#include <stdio.h>

main() {
  return 0;
}

char *lastnstr(char *s, int maxlen) {
  register char *cs;

  cs = s;
  while(maxlen-- && *s) s++;
  if(*s == '\0')
    return cs;
  while(*s++) cs++;
  return cs;
}

#include <stdio.h>
#include <string.h>

#define symboltostr_helper(A) #A
#define symboltostr(A) symboltostr_helper(A)

char *lastnstr(char *, int);

#define COLPAGE "page "
/* line column contains logical info like title or page */
#define COLCLIP "..."
/* col should be able to contain title rest part, i.e. MAXLINECOL > COLCLIP */
#define MAXLINECOL 16

int printpagehead(char *title, int page, int maxline, FILE *fp) {
  int pslen;
  char *trimtitle;
  int lw;

  lw = maxline - 1;
  if(lw < MAXLINECOL * 2) {
    fprintf(stderr, "header line should be able to contain title, page cols of size %d.\n", MAXLINECOL);
    return EOF;
  }

  while(lw-- && putc('-', fp) != EOF);
  if(ferror(fp))
    return EOF;
  if(putc('\n', fp) == EOF)
    return EOF;

  /* this is possible to implement in more easy manner
    using char col[] and rewrite start part if title
    exceeded column limit.
  */
  if((trimtitle = lastnstr(title, MAXLINECOL)) != title)
    fprintf(fp, COLCLIP "%-s", trimtitle + sizeof(COLCLIP));
  else
    fprintf(fp, "%-" symboltostr(MAXLINECOL) "s", title);

  if(ferror(fp))
    return EOF;
}
