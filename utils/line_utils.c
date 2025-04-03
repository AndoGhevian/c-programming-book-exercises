#include <stdio.h>
#include <string.h>
#include "../utils/alloc.h"

#define MAXLENS 100

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
  char line[MAXLENS + 1];

  nlines = 0;
  while((len = getline_cm(line, MAXLENS)) > 0)
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
  char (*linestorage), line[MAXLENS + 1];
  int nlines = 0, len;

  while(++nlines <= maxlines && (len = getline_cm(line, MAXLENS))) {
    if(line[len - 1] == '\n')
      line[--len] = '\0';

    if(linestorage = alloc(len + 1))
      *lineptr++ = strcpy(linestorage, line);
    else
      return -1;
  }

  return --nlines;
}

void writelines(char *lineptr[], int nlines) {
  while(nlines-- > 0)
    printf("%s\n", *lineptr++);
}
