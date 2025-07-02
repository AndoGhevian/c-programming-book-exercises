#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
char s1[MAXLINE], s2[MAXLINE];

main(int argc, char *argv[]) {
  char *prog;
  int nline;
  FILE *fp1, *fp2;

  prog = argc >= 1 ? *argv : "unnamed";
  if(argc < 3 || argc > 3) {
    fprintf(stderr, "command %s: expected 2 filename arguments to compare.\n", prog);
    exit(2);
  }

  fp1 = fopen(argv[1], "r");
  fp2 = fopen(argv[2], "r");

  nline = cmpfilelines(fp1, fp2, s1, s2, MAXLINE);
  if(nline == EOF) {
    fprintf(stderr, "command %s: error while comparing files %s <> %s.\n", prog, argv[1], argv[2]);
    exit(3);
  } else if(nline == 0) {
    fprintf(stderr, "command %s: files %s, %s are compared equal.\n", prog, argv[1], argv[2]);
  } else {
    fprintf(stderr, "command %s: files %s, %s are not equal at line %d.\n", prog, argv[1], argv[2], nline);
    fprintf(stderr, "%s\n%s\n", s1, s2);

    /* program output for subsequent usage by caller */
    fprintf(stdout, "%d", nline);
  }

  return 0;
}

/* returns len when equal and -1 otherwise */
int strcmp_retlen(char *, char *);

/* returns line number where they differ, EOF on error or 0 on equality.
  if error occurres, compared strings are indeterminate.

  note: the reason of indeterminate strings on error is not only the ANSI C
  standard fgets handling way, but rather the logical fact of inability
  to compare lines.
*/
int cmpfilelines(FILE *fp1, FILE *fp2, char *s1, char *s2, int maxline) {
  int n, len;

  len = 0;
  n = 1;
  while(fgets(s1, maxline, fp1) != NULL && fgets(s2, maxline, fp2) != NULL && (len = strcmp_retlen(s1, s2)) > 0)
    if(s1[len - 1] == '\n')
      n++;

  if(ferror(fp1) || ferror(fp2))
    return EOF;
  if(len < 0)
    return n;
  return 0;
}

int strcmp_retlen(char *s1, char *s2) {
  int len;

  for(len = 0; *s1 == *s2; s1++, s2++)
    if(*s1 != '\0')
      len++;
    else
      return len;
  return -1;
}
