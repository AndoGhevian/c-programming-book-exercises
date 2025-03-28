#include <stdlib.h>
#include <stdio.h>
#include "../utils/line_utils.h"

#define MAXPARAMS 100
#define DEFAULTTABSTOP 4

#ifndef DETABCMD
#define MAXOUTPUT 10000 /* '\t' replaced blanks >= 1 blank */
#define MAXLEN 10000
main(int argc, char *argv[]) {
  int paramlen, c, nblank, nspace;

  char tabstops[MAXPARAMS];
  char *tabstopptr = tabstops;

  char input[MAXLEN];
  char *inptr = input;

  char output[MAXOUTPUT];
  char *outptr = output;

  paramlen = argc - 1;
  if(paramlen > MAXPARAMS) {
    printf("program parameters maximum count is %d\n", MAXPARAMS);
    return -1;
  }

  while(tabstopptr < tabstops + paramlen)
    *tabstopptr++ = atoi(*++argv);
  tabstopptr = tabstops;

  if(getlines(input, MAXLEN - 1) == -1) {
    printf("input string must be not more than %d characters length\n", MAXLEN - 1);
    return -2;
  }

  nblank = nspace = 0;
  while(c = *inptr++)
    switch(c) {
      case '\n':
        nblank = 0;
        tabstopptr = tabstops;
        *outptr++ = '\n';

        nspace = 0;
        break;
      case ' ':
        nspace++;
        *outptr++ = ' ';
        if(++nblank == (tabstopptr < tabstops + paramlen ? *tabstopptr : DEFAULTTABSTOP)) {
          outptr -= nspace;

          nspace = 0;
          nblank = 0;
          if(tabstopptr != tabstops + paramlen)
            tabstopptr++;
          *outptr++ = '\t';
        }
        break;
      case '\t':
        nblank = 0;
        if(tabstopptr != tabstops + paramlen)
          tabstopptr++;
        *outptr++ = '\t';

        nspace = 0;
        break;
      default:
        if(++nblank == (tabstopptr < tabstops + paramlen ? *tabstopptr : DEFAULTTABSTOP)) {
          nblank = 0;
          if(tabstopptr != tabstops + paramlen)
            tabstopptr++;
        }
        *outptr++ = c;

        nspace = 0;
    }
  *outptr = '\0';


  /* uncomment for visual representation of terminal tabstops */
  /* printf("\n0\t0\t0\t0\t0\t\n"); */
  printf("%s\n", output);

  return 0;
}
#else
#define MAXOUTPUT 20000
#define MAXLEN 10000
main(int argc, char *argv[]) {
  int i, paramlen, c, nblank;

  int tabstops[MAXPARAMS + 1];
  int *tabstopptr = tabstops;

  char input[MAXLEN];
  char *inptr = input;

  char output[MAXOUTPUT];
  char *outptr = output;

  paramlen = argc - 1;
  if(paramlen > MAXPARAMS) {
    printf("acceptable maximum program parameters count is %d", MAXPARAMS);
    return -2;
  }

  for(i = 0; i < paramlen; i++)
    tabstops[i] = atoi(argv[i + 1]);

  if(getlines(input, MAXLEN - 1) == -1) {
    printf("input storage array limit exceeded, its length is %d"
      , MAXLEN);
    return -1;
  }

  nblank = 0;
  while((c = *inptr++) && outptr - output < MAXOUTPUT - 1)
    switch(c) {
      case '\n':
        nblank = 0;
        tabstopptr = tabstops;
        *outptr++ = '\n';
        break;
      case '\t':
        while(++nblank <= (tabstopptr < tabstops + paramlen ? *tabstopptr : DEFAULTTABSTOP))
          *outptr++ = ' ';
        if(tabstopptr < tabstops + paramlen)
          tabstopptr++;
        nblank = 0;
        break;
      default:
        if(++nblank == (tabstopptr < tabstops + paramlen ? *tabstopptr : DEFAULTTABSTOP)) {
          if(tabstopptr < tabstops + paramlen)
            tabstopptr++;
          nblank = 0;
        }
        *outptr++ = c;
        break;
    }
  *outptr = '\0';

  printf("\n%s", output);

  return 0;
}
#endif
