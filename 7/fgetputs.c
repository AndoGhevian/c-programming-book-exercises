#include <stdio.h>

char *local_fgets(char *, int, FILE *);
int local_fputs(char const *, FILE *);

#define MAXLINE 1000
char line[MAXLINE];

main() {
  while(local_fgets(line, MAXLINE, stdin) != NULL && local_fputs(line, stdout) != EOF);

  return 0;
}

/* see ANSI C 4.9.7.1 */
char *local_fgets(char *s, int n, FILE *stream) {
  register int c;
  register char *cs;

  cs = s;
  while(--n > 0 && (c = getc(stream)) != EOF)
    if((*cs++ = c) == '\n')
      break;
  if(cs != s)
    *cs = '\0';

  if(ferror(stream))
    return NULL;
  return c == EOF && cs == s ? NULL : s;
}

/*see ANSI C 4.9.7.4 */
int local_fputs(char const *s, FILE *stream) {
  while(*s != '\0' && putc(*s, stream) != EOF) s++;

  if(ferror(stream))
    return EOF;
  return 0;
}
