#include <stdlib.h>
#include <stdio.h>
#include "../utils/line_utils.h"

#define MAXINPUT 10000
#define MAXOUTPUT 20000
#define MAXPARAMS 100
#define DEFAULTTABSIZE 4

/*
  By default if no arguments provided
  command is supposed to be called with
  -0 +0 arguments.

  +n or n argument:
  1. if preceeded by -m then will continue with tab size n from last tabstop declared by -m.
  2. If preceeded by +k, like +k +n, then will act as -0 +k -k +n,
      like if one tab already done by tab size k and the rest is continued by tab size n.
  3. 0 is special, +0 and 0 is handled as if default tab size of a program is used.
      so in case of +0 +n it will be handled not as if -0 +n but as -DEFAULTTABSIZE +n.
  4. If +n or n is a first argument then it overrides default +0 not preceeded by it,
      e.g. entab +4 <=> entab -0 +4

  -m argument:
  1. -m adds a tabstop in the column m counted from last tabstop position.

Input is considered to be started after the tab stop (-1 char *).
Usage example: entab +5 -4 0
*/
main(int argc, char *argv[]) {
  char **argvptr;

  char c, input[MAXINPUT + 1];
  char *inptr = input;

  char output[MAXOUTPUT];
  char *outptr = output;

  int tabstopbrk, tabsize;
  int col;
  int is_sequential_tabsize;

  int paramlen = argc - 1;
  if(paramlen > MAXPARAMS) {
    printf("maximum program parameters count is %d\n", MAXPARAMS);
    return -1;
  }

  if(getlines(input, MAXINPUT) == -1) {
    printf("input maximum length is %d\n", MAXINPUT);
    return -2;
  }

  #define init_tab_scaner()\
  argvptr = argv;\
  col = 1;\
  tabsize = DEFAULTTABSIZE;\
  is_sequential_tabsize = 0;

  init_tab_scaner();
  c = *inptr;
  while(argvptr - argv + 1 <= argc) {
    if(*++argvptr)
      switch(*argvptr[0]) {
        case '-':
          is_sequential_tabsize = 0;
          tabstopbrk = -1 * atoi(*argvptr);
          break;
        case '+':
        default:
          if(!is_sequential_tabsize++) {
            tabsize = (tabsize = atoi(*argvptr)) ? tabsize : DEFAULTTABSIZE;
            continue;
          }
          is_sequential_tabsize = 0;
          tabstopbrk = tabsize;
          argvptr--;
          break;
      }
    else
      tabstopbrk = -1;

    int newline = 0;
    while(!newline && tabstopbrk && (c = *inptr++))
      switch(c) {
        case '\n':
          newline = 1;
          init_tab_scaner();
          *outptr++ = '\n';
          break;
        case '\t':
          #ifndef ENTAB
          do
            *outptr++ = ' ';
          while(--tabstopbrk && ++col <= tabsize);
          col = 1;
          #endif
          break;
        default:
          #ifndef ENTAB
          tabstopbrk--;
          if(col++ == tabsize)
            col = 1;
          *outptr++ = c;
          #endif
          break;
      }

    if(!c)
      break;
  }
  *outptr = '\0';

  printf("%s\n", output);

  return 0;
}
