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
char *local_fgets(char *s, int n, FILE *stream);

/*see ANSI C 4.9.7.4 */
int local_fputs(char const *s, FILE *stream);
