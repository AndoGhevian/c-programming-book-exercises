#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "calc.h"
/*
test for multiple inclusions of a header with 
multiple definitions of variables and functions.

as compilation process including:
1. preproccessing, 2. compilation
3. assemble, are bounded to a single source
file, these inclusions can produce conflicts
only if these definitions are not conditional.

In case of multiple inclusions of a header with definitions
(with or without conditions) are error in the linking stage.

*/

/* #include "deftest.h"
#include "deftest.h"
#include "deftest.h" */


#define MAXOP 100
double vars[26];

main() {
  int type;
  double op2, sw1, sw2;
  int vc;
  char s[MAXOP];
  int sr = 0; /* skip return */
  /* uncomment bellow code to test multiple definitions linker error */
/* 
  printf("\n\n %d \n \n", lerx);
  lerxprint();
   */
  void ungets(char s[]);
  int getch_many(void);
  int i;
  char stest[] = "hello";
  ungets(stest);

  printf("testing ungets(s), test_string=\"%s\"\n", stest);
  for(i = 0; i < strlen(stest); i++)
    putchar(getch_many());
  putchar('\n');

  vc = -1;
  while((type = getop(s)) != EOF) {
    if(type != '=')
      vc = -1;
    switch(type) {
      case VAR:
        vc = tolower(s[0]);
        push(vars[vc - 'a']);
        break;
      case NUMBER:
        push(atof(s));
        break;
      case '=':
        if(vc == -1)
          printf("Invalid assignment to rvalue\n");
        else {
          pop();
          push(vars[vc - 'a'] = pop());
        }
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        op2 = pop();
        push(pop() - op2);
        break;
      case '/':
        op2 = pop();
        push(pop() / op2);
        break;
      case '%':
        op2 = pop();
        push((int)pop() % (int)op2);
        break;
      case SIN:
        push(sin(pop()));
        break;
      case EXP:
        push(pow(10, pop()));
        break;
      case POW:
        op2 = pop();
        push(pow(pop(), op2));
        break;
      case PRINT:
        sr = 1;
        break;
      case SWAP:
        sw1 = pop();
        sw2 = pop();
        push(sw1);
        push(sw2);
        break;
      case DUPLICATE:
        push(op2 = pop());
        push(op2);
        break;
      case CLEAR:
        clear();
        break;
      case '\n':
        if(sr)
          print();
        else
          printf("\t%.8g\n", pop());
        sr = 0;
        break;
      default:
        printf("error: unknown command %s\n", s);
        break;
    }
  }

  return 0;
}
