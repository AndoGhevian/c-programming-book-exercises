#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../utils/line_utils.h"
#include "../utils/alloc.h"

int casei = 1;
int numcomp(char *s1, char *s2);
int dictcomp(char *s1, char *s2);
int strcomp(char *s1, char *s2);

int compare(char *e1, char *e2);

/* note, after quick sort, equal elements are shuffled */
void qsort_excercise(void *v[], int left, int right, int (*comp)(void *, void *));

#define MAXLINES 100
int nlines = 0;
char *lineptr[MAXLINES];

#define MAX_COMMAND_LINE_ARGS 100
#define MAX_FIELD_CMP MAX_COMMAND_LINE_ARGS / 2 + MAX_COMMAND_LINE_ARGS % 2
int (*cmpptr[MAX_FIELD_CMP])(char *, char *);
int caseinsense[MAX_FIELD_CMP];
int reverse[MAX_FIELD_CMP];
char *brkptr[MAX_FIELD_CMP];

/*
  Apply quick sort on fields of a string.

  Fields are breaked by a parameters provided
  after -b flags.
  Sorting configuration parameters should be provided
  before or with -b parameter.
  e.g. qsort -n -f -bd ", " -bnf -

  Sequential fields are searched after last break part
  provided by -b parameter.
  If field indicated by -b parameter is not found
  then it is considered to be "empty string".

  If -b parameter is "empty string", then sorting
  will be performed, and sequential sorting/breaks will be
  continued from the same position, like no break is happened.

  See Compare function implementation.
  The downside of this implementation, is
  that when one string does not contain field breaker
  appropriate field is considered to be empty string.

  It will be convinient from user perspective in case
  if one contains field breaker and second is not,
  then the rest of that second string consider as the content of a whole field.
*/
main(int argc, char *argv[]) {
  extern int caseinsense[], reverse[];

  int i, nextbrk, cise, rves;
  int (*comp)(char *, char *);

  nextbrk = i = 0;
  rves = 1;
  cise = 0;
  comp = (int (*)(char *, char *))strcomp;
  while(*++argv)
    /* nextbrk && !(nextbrk = 0) - use nextbrk and reset in single expr */
    if(nextbrk) {
      cmpptr[i] = (int (*)(char *, char *))comp;
      caseinsense[i] = cise;
      reverse[i] = rves;
      brkptr[i] = *argv;

      /* reset sorting parameters */
      comp = (int (*)(char *, char *))strcomp;
      rves = 1;
      cise = 0;

      nextbrk = 0;
      i++;
    } else if((*argv)[0] == '-') {
      if(strstr(*argv, "b"))
        nextbrk = 1;

      if(strstr(*argv, "n"))
        comp = (int (*)(char *, char *))numcomp;
      else if(strstr(*argv, "d"))
        comp = (int (*)(char *, char *))dictcomp;

      if(strstr(*argv, "r"))
        rves = -1;
      if(strstr(*argv, "f"))
        cise = 1;
    }

  cmpptr[i] = (int (*)(char *, char *))comp;
  caseinsense[i] = cise;
  reverse[i] = rves;
  brkptr[i] = NULL; /* means until the end of the string */

  if((nlines = readlines(lineptr, MAXLINES)) < 0) {
    printf("no enough memory space to store input\n");
    return -1;
  }

  qsort_excercise((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))compare);

  printf("\n");
  writelines(lineptr, nlines);

  return 0;
}


/* >>> compare functions >>> */

int strcomp(char *s1, char *s2) {
  extern int casei;
  int cmp;

  while(*s1 && *s2)
    if(cmp = casei ?
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
  extern int casei;
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

    comp = casei ? tolower(*s1) - tolower(*s2) : *s1 - *s2;
    if(comp)
      return comp;
    else if(s1 == 0 && s2 == 0)
      return 0;
  } while(*++s1 && *++s2);

  return *s1 - *s2;
}

/* <<< compare functions <<< */


int compare(char *e1, char *e2) {
  extern int (*cmpptr[])(char *e1, char *e2);
  extern int caseinsense[];
  extern int reverse[];
  extern char *brkptr[];

  char *sptr1, *sptr2;
  int i, comp;
  for(i = 0, casei = caseinsense[i]; brkptr[i]; i++) {
    casei = caseinsense[i];
    sptr1 = strstr(e1, brkptr[i]);
    sptr2 = strstr(e2, brkptr[i]);
    if(!sptr1 && !sptr2)
      continue;
    else if(!sptr1)
      return -reverse[i];
    else if(!sptr2)
      return reverse[i];
    else {
      int brklen = strlen(brkptr[i]);
      char prevc1, prevc2;
      prevc1 = *sptr1;
      prevc2 = *sptr2;
      if(brklen) {
        *sptr1 = '\0';
        *sptr2 = '\0';
      }

      comp = cmpptr[i](e1, e2);
      *sptr1 = prevc1;
      *sptr2 = prevc2;
      if(comp)
        return reverse[i] * comp;
      e1 = sptr1 + brklen;
      e2 = sptr2 + brklen;
    }
  }

  casei = caseinsense[i];
  return reverse[i] * cmpptr[i](e1, e2);
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
