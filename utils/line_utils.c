#include <stdio.h>
#include <string.h>

/* second argument declares string maximum length (null character not included)*/
int getline_cm(char *line, int maxlen) {
  char *sline = line;
  int c, len = 0;

  while(line - sline < maxlen && (c = getchar()) != '\n' && c != EOF)
    *line++ = c;
  if(c == '\n')
    *line++ = '\n';
  *line = '\0';

  return line - sline;
}

#define MAXLENS 100
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
