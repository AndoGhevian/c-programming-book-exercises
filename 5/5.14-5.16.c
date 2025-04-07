#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../utils/line_utils.h"
#include "../utils/alloc.h"

int caseinsense = 0;
int numcomp(char *s1, char *s2);
int dictcomp(char *s1, char *s2);
int strcomp(char *s1, char *s2);

/* note, after quick sort, equal elements are shuffled */
void qsort_excercise(void *v[], int left, int right, int (*comp)(void *, void *));

int reverse = 1; /* inc: >= 0, dec: < 0 */
int (*comp)(void *e1, void *e2);
int compare(void *e1, void *e2);

#define MAXLINES 100
int nlines = 0;
char *lineptr[MAXLINES];

main(int argc, char *argv[]) {
  extern int caseinsense, reverse;
  extern int (*comp)(void *, void *);

  int i;
  comp = (int (*)(void *, void *))strcomp;

  while(*++argv)
    if((*argv)[0] == '-') {
      if(strstr(*argv, "n"))
        comp = (int (*)(void *, void *))numcomp;
      else if(strstr(*argv, "d"))
        comp = (int (*)(void *, void *))dictcomp;

      if(strstr(*argv, "r"))
        reverse = -1;
      if(strstr(*argv, "f"))
        caseinsense = 1;
    }

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

int strcomp(char *s1, char *s2) {
  extern int caseinsense;
  int cmp;

  while(*s1 && *s2)
    if(cmp = caseinsense ?
        tolower(*s1++) - tolower(*s2++)
        : *s1++ - *s2++)
      return cmp;

  return *s1 - *s2;
}

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

int dictcomp(char *s1, char *s2) {
  extern int caseinsense;
  int comp, c1, c2;

  do {
    while(*s1)
      if(isalnum(*s1) || *s1 == ' ')
        break;
      else
        s1++;

    while(*s2)
      if(isalnum(*s2) || *s2 == ' ')
        break;
      else
        s2++;

    comp = caseinsense ? tolower(*s1) - tolower(*s2) : *s1 - *s2;
    if(comp)
      return comp;
    else if(s1 == 0 && s2 == 0)
      return 0;
  } while(*++s1 && *++s2);

  return *s1 - *s2;
}

/* <<< compare functions <<< */


int compare(void *e1, void *e2) {
  extern int reverse;
  extern int (*comp)(void *e1, void *e2);

  if(!comp)
    return 0;
  return reverse * comp(e1, e2);
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
