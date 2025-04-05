#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../utils/line_utils.h"
#include "../utils/alloc.h"

int numcomp(char *s1, char *s2);

#define MAX_TRANSFORMLINE MAX_LINESTRLENS * 2
char *t_tolower(char *s);

/* note, after quick sort, equal elements are shuffled */
void qsort_excercise(void *v[], int left, int right, int (*comp)(void *, void *));

void configcompare(int (void *, void *));
void configorder(int o);
int compare(void *e1, void *e2);

#define MAXLINES 100
int nlines = 0;
char *lineptr[MAXLINES];
char *translineptr[MAXLINES];

char *transmap[MAXLINES];
char *linemap[MAXLINES];
int complinesbymap(char *l1, char *l2);

main(int argc, char *argv[]) {
  int i, caseinsense = 0;
  configcompare((int (*)(void *, void *))strcmp);
  configorder(1);

  while(*++argv)
    if((*argv)[0] == '-') {
      if(strstr(*argv, "n"))
        configcompare((int (*)(void *, void *))numcomp);
      if(strstr(*argv, "r"))
        configorder(-1);
      if(strstr(*argv, "f"))
        caseinsense = 1;
    }
    

  if((nlines = readlines(lineptr, MAXLINES)) < 0) {
    printf("no enough memory space to store input\n");
    return -1;
  }

  for(i = 0; i < nlines; i++) {
    linemap[i] = lineptr[i];
    transmap[i] = translineptr[i] = strcpy(alloc(MAX_TRANSFORMLINE), lineptr[i]);
    if(caseinsense)
      t_tolower(translineptr[i]);
  }

  qsort_excercise((void **)translineptr, 0, nlines - 1, compare);
  qsort_excercise((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))complinesbymap);

  printf("\n");
  writelines(lineptr, nlines);

  return 0;
}


/* >>> transform functions */

char *t_tolower(char *s) {
  char *start_s = s;
  int c;
  while(c = *s)
    *s++ = tolower(c);
  return start_s;
}

/* <<< transform functions */


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

int complinesbymap(char *l1, char *l2) {
  extern char *translineptr[MAXLINES];
  extern char *transmap[MAXLINES];
  extern char *linemap[MAXLINES];

  int i, t1, t2;
  char *tptr1, *tptr2;

  t1 = t2 = -1;
  for(i = 0; i < MAXLINES && linemap[i]; i++)
    if(t1 != -1 && t2 != -1)
      break;
    else {
      if(linemap[i] == l1)
        t1 = i;
      if(linemap[i] == l2)
        t2 = i;
    }

  tptr1 = transmap[t1];
  tptr2 = transmap[t2];
      
  if(tptr1 == tptr2)
    return 0;

  for(i = 0; translineptr[i] != tptr1 && translineptr[i] != tptr2; i++);

  if(translineptr[i] == tptr1)
    return -1;
  else
    return 1;
}
