/* 5.10 */
#include <stdio.h>
#include <stdlib.h>

#define MAXOPS 100

int getop(char *c);
/* no check of stack overflow */
extern double *opstack;

main(int argc, char **argv) {
  char opc;
  char **vs = argv;
  char **opdp;
  while(*++argv)
    if(!(opc = getop(*argv)))
      continue;
    else {
      int foundn = 0;
      double ops[2] = {0.0, 0.0};

      opdp = argv;
      while(foundn != 2 && --opdp > vs)
        if(*opdp)
          if(getop(*opdp))
            ops[1 - foundn++] = *--opstack;
          else
            ops[1 - foundn++] = atof(*opdp);
        else
          *opdp = 0;

      switch(opc) {
        case '+':
          *opstack++ = ops[0] + ops[1];
          break;
        case '-':
          *opstack++ = ops[0] - ops[1];
        case '%':
          *opstack++ = (long int)ops[0] % (long int)ops[1];
          break;
        case '/':
          *opstack++ = ops[0] / ops[1];
          break;
        case '*':
          *opstack++ = ops[0] * ops[1];
          break;
        default:
          break;
      }
    }

  if(--argv == vs)
    printf("Provide polish format expression!!!\n");
  else if(getop(*argv))
    printf("%f\n", *--opstack);
  else
    printf("%s\n", *argv);

  return 0;
}

int getop(char *c) {
  switch(*c) {
    case '+':
    case '-':
    case '%':
    case '/':
    case '*':
      if(!*(c + 1))
        return *c;
      break;
    default:
      break;
  }
  return '\0';
}

double opv[MAXOPS];
double *opstack = opv;
