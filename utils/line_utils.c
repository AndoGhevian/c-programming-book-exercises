#include <stdio.h>

int getline_cm(char *line, int maxlen) {
  char *sline = line;
  int c, len = 0;

  while(line - sline <= maxlen && (c = getchar()) != '\n' && c != EOF)
    *line++ = c;
  if(c == '\n')
    *line++ = '\n';
  *line = '\0';

  return line - sline;
}
