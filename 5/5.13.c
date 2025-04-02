#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "../utils/alloc.h"
#include "../utils/line_utils.h"

/* optional parameter types */
#define PARAMLINESNUM 1
int optparamtype(char *param);

#define MAXLINESNUMBER 4
int readnlines(char *lineptr[], int n);

void writelines(char const * const lineptr[], int startline_index);

main(int argc, char *argv[]) {
  int maxlines = MAXLINESNUMBER;
  /* last pointer is always 0 pointer */
  char *lineptr[MAXLINESNUMBER + 1] = { 0 };
  char **lptr = lineptr;
  int prevnlines, nlines;

  while(*++argv)
    switch((*argv)[0]) {
      case '-':
        switch(optparamtype(*argv)) {
          case PARAMLINESNUM:
            maxlines = -1 * atoi(*argv);
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }

  maxlines = maxlines ? maxlines : MAXLINESNUMBER;

  while(prevnlines = nlines, nlines = readnlines(lineptr, maxlines))
    if(nlines == -1) {
      printf("no enough space to hold %d lines of strings in memory", maxlines);
      return -1;
    }

  printf("\n");
  writelines((char const *const *)lineptr, prevnlines);

  /* free readlines allocated storag */
  if(*lineptr)
    /* in current afree inplementation this will clear the rest of storage */
    afree(*lineptr);
  return 0;
}

int optparamtype(char *param) {
  int isd = -1;

  int i, c;
  while(*++param)
    if(!isdigit(*param))
      isd = 0;
    else if(isd)
      isd = 1;

  if(isd == 1)
    return PARAMLINESNUM;
}

#define MAXLEN 1000
int readnlines(char *lineptr[], int maxlines) {
  int len, nlines;
  char *p, line[MAXLEN + 1];

  nlines = 0;
  while(nlines < maxlines && (len = getline_cm(line, MAXLEN)) > 0) {
    if(!*lineptr)
      if(p = alloc(MAXLEN + 1))
        *lineptr = p;
      else
        return -1;
    if(line[len - 1] == '\n')
      line[--len] = '\0';
    strcpy(*lineptr++, line);
    nlines++;
  }

  return nlines;
}

/* lineptr must have last element 0 pointer */
void writelines(const char * const lineptr[], int startline_index) {
  char const * const *lptr = lineptr + startline_index;

  while(*lptr)
    printf("%s\n", *lptr++);

  lptr = lineptr;
  while(lptr < lineptr + startline_index)
    printf("%s\n", *lptr++);
}
