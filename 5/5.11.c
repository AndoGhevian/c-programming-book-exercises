#include <stdlib.h>
#include <stdio.h>
#include "../utils/line_utils.h"

#define MAXOUTPUT 20000
#define MAXLEN 10000
#define MAXPARAMS 100
#define DEFAULTTABSTOP 4

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
