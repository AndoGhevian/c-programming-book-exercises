#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/line_utils.h"

int numcomp(char *s1, char *s2);

void qsort_excercise(void *v[], int left, int right, int (*comp)(void *, void *));

void configcompare(int (void *, void *));
void configorder(int o);
int compare(void *e1, void *e2);

#define MAXLINES 100
char *lineptr[MAXLINES];
int nlines = 0;

main(int argc, char *argv[]) {
  configcompare((int (*)(void *, void *))strcmp);
  configorder(1);

  while(*++argv)
    if(strcmp(*argv, "-n") == 0)
      configcompare((int (*)(void *, void *))numcomp);
    else if(strcmp(*argv, "-r") == 0)
      configorder(-1);

  if((nlines = readlines(lineptr, MAXLINES)) < 0) {
    printf("no enough memory space to store input\n");
    return -1;
  }

  qsort_excercise((void **)lineptr, 0, nlines - 1, compare);

  printf("\n");
  writelines(lineptr, nlines);

  return 0;
}

/* >>> compare functions >>> */

int numcomp(char *s1, char *s2) {
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);

  if(v1 < v2)
    return -1;
  else if(v1 > v2)
    return 1;
  else
    return 0;
}

/* <<< compare functions <<< */


int (*comp)(void *e1, void *e2);
int reverse = 1; /* inc: 1, dec: -1 */
int compare(void *e1, void *e2) {
  if(!comp)
    return 0;
  return reverse * comp(e1, e2);
}

void configcompare(int c(void *, void *)) {
  comp = c;
}

/* < 0 dec, >= 0 inc */
void configorder(int o) {
  reverse = o < 0 ? -1 : 1;
}

void qsort_excercise(void *v[], int left, int right, int comp(void *, void *)) {
  int i, last;
  void swap(void *v[], int i, int j);

  if(left >= right)
    return;
  swap(v, left, (right + left) / 2);
  last = left;
  for(i = left + 1; i <= right; i++)
    if(comp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, last, left);
  qsort_excercise(v, left, last - 1, comp);
  qsort_excercise(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j) {
  void *temp = v[i];

  v[i] = v[j];
  v[j] = temp;
}
