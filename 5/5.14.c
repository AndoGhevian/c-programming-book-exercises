#include <stdio.h>
#include <string.h>
#include "../utils/line_utils.h"

void qsort(void *v[], int left, int right, int (*comp)(void *, void *));

int compare(void *e1, void *e2);
void settransform(void *t(void *));
void setcomp(int c(void *, void *));
void setreverse(int r);

#define MAXLINES 100
char *lineptr[MAXLINES];
int nlines = 0;
int numeric = 0, dec = 0, casesense = 1;

main(int argc, char *argv[]) {
  while(*++argv)
    if(strcmp(*argv, "-n"))
      numeric = 1;
    else if(strcmp(*argv, "-r"))
      dec = 1;
    else if(strcmp(*argv, "-f"))
      casesense = 0;


  if((nlines = readlines(lineptr, MAXLINES)) < 0) {
    printf("no enough memory space to store input\n");
    return -1;
  }

  qsort((void **)lineptr, 0, nlines - 1, compare);
  printf("\n");
  writelines(lineptr, nlines);

  return 0;
}

void *(*transform)(void *e);
int (*comp)(void *e1, void *e2);
int reverse = 1; /* inc: 1, dec: -1 */
int compare(void *e1, void *e2) {
  if(!comp)
    return 0;
  if(!transform)
    return reverse * comp(e1, e2);

  return reverse * comp(transform(e1), transform(e2));
}

void settransform(void *t(void *)) {
  transform = t;
}

void setcomp(int c(void *, void *)) {
  comp = c;
}

void setreverse(int r) {
  reverse = r;
}
