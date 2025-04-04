#include <stdio.h>
#include <string.h>
#include "line_utils.h"
#include "alloc.h"

/* second argument declares string maximum length (null character not included)*/
int getline_cm(char *line, int maxlen) {
  char *sline = line;
  int c;

  while(line - sline < maxlen && (c = getchar()) != '\n' && c != EOF)
    *line++ = c;
  if(c == '\n')
    *line++ = '\n';
  *line = '\0';

  return line - sline;
}

int getlines(char input[], int maxinputlen) {
  char *inputptr = input;
  int len, nlines;
  char line[MAX_LINESTRLENS + 1];

  nlines = 0;
  while((len = getline_cm(line, MAX_LINESTRLENS)) > 0)
    if(input + maxinputlen - inputptr - 1 < len)
      return -1;
    else {
      strncpy(inputptr, line, len);
      inputptr += len;
      nlines++;
    }
  *inputptr = '\0';
  return nlines;
}

/*
  this function is different from function in book:
  it reads maxmium provided count of lines and stops,
  in the book it reads until user stops manually with EOF,
  if you read more than maximum count it crashes. 
*/
int readlines(char *lineptr[], int maxlines) {
  char (*linestorageptr), line[MAX_LINESTRLENS + 1];
  int nlines = 0, len;

  while(++nlines <= maxlines && (len = getline_cm(line, MAX_LINESTRLENS))) {
    if(line[len - 1] == '\n')
      line[--len] = '\0';

    if(linestorageptr = alloc(len + 1))
      *lineptr++ = strcpy(linestorageptr, line);
    else {
      int nclear = nlines;
      while(--nclear)
        afree(*--lineptr);
      return -nlines;
    }
  }

  return --nlines;
}

void writelines(char *lineptr[], int nlines) {
  while(nlines-- > 0)
    printf("%s\n", *lineptr++);
}
