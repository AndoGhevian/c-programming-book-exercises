#include <stdio.h>
#include <string.h>
#include "../utils/line_utils.h"
#include "../utils/alloc.h"

#define MAXLINES 5000
#define LINESTORAGE 10

char *lineptr[MAXLINES];
char linebuff[LINESTORAGE];

int readlines_local(char *lineptr[], char linebuff[], int bufsize, int nlines);
void writelines_local(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

main() {
  int nlines;
  /* printf("%d %d %d", '0' > '1', '1' > '2', '1' > 'a'); */

  if((nlines = readlines_local(lineptr, linebuff, LINESTORAGE, MAXLINES)) >= 0) {
    printf("\n");
    qsort(lineptr, 0, nlines - 1);
    writelines_local(lineptr, nlines);
    return 0;
  } else {
    printf("error: input is too big to sort.\n");
    return 1;
  }

  return 0;
}

void swap(char *lineptr[], int i, int j);

void qsort(char *lineptr[], int left, int right) {
  int i, last;
  if(left >= right)
    return;
  swap(lineptr, left, (left + right) / 2);
  last = left;
  for(i = left + 1; i <= right; i++)
    if(strcmp(lineptr[left], lineptr[i]) > 0)
      swap(lineptr, i, ++last);
  swap(lineptr, left, last);
  qsort(lineptr, left, last - 1);
  qsort(lineptr, last + 1, right);
}

void swap(char *lineptr[], int i, int j) {
  char *temp;

  temp = lineptr[i];
  lineptr[i] = lineptr[j];
  lineptr[j] = temp;
}

#define MAXLEN 1000

int readlines_local(char *lineptr[], char linebuff[], int bufsize, int maxlines) {
  int len, nlines;
  char *p = linebuff, line[MAXLEN];

  nlines = 0;
  while((len = getline_cm(line, MAXLEN - 1)) > 0) {
    if(line[len - 1] == '\n')
      line[--len] = '\0';
    if(nlines > maxlines || p + len - linebuff + 1 > bufsize) {
      return -1;
    }

    strcpy(p, line);
    lineptr[nlines++] = p;
    p += len + 1;
  }
  return nlines;
}

void writelines_local(char *lineptr[], int nlines) {
  int i;
  for(i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}
