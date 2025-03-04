#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXOP 100
/*
  make sure those are greater than max('A', '9')
  for any character set.
*/
enum cmd {
  NUMBER = 'A' + '9',
  PRINT,
  DUPLICATE,
  SWAP,
  CLEAR,
  SIN,
  EXP,
  POW,
};

double atof(char s[]);

void push(double val);
double pop(void);
enum cmd getop(char s[]);
void print(void);
void clear(void);

main() {
  int type;
  double op2, sw1, sw2;
  char s[MAXOP];
  int sr = 0; /* skip return */

  while((type = getop(s)) != EOF)
    switch(type) {
      case NUMBER:
        push(atof(s));
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

  return 0;
}

#define CALBUFSIZE 100

double calbuf[CALBUFSIZE];
int calbufp = 0;

void push(double val) {
  if(calbufp < CALBUFSIZE)
    calbuf[calbufp++] = val;
  else
    printf("Calculator stack is full, can't push\n");
}

double pop(void) {
  if(calbufp > 0)
    return calbuf[--calbufp];
  else {
    printf("Calculator is empty\n");
    return 0.0;
  }
}

void print(void) {
  int i;
  for(i = 0; i < calbufp; i++)
    printf("%g ", calbuf[i]);
}

void clear(void) {
  calbufp = 0;
}

int getch(void);
void ungetch(int);

enum cmd getop(char s[]) {
  int i, c;

  while((s[0] = c = getch()) == ' ' && isspace(c));
  s[1] = '\0';
  
  i = 0;
  if(s[0] == '-' || s[0] == '+' || isdigit(s[0]))
    while(isdigit(s[++i] = c = getch()));

  if(c == '.')
    while(isdigit(s[++i] = c = getch()));

  if(isalpha(s[0]))
    while(isalpha(s[++i] = c = getch()));

  if(i != 0) {
    s[i] = '\0';
    if(c != EOF)
      ungetch(c);
  }

  if(isdigit(s[0]))
    return NUMBER;

  if(i == 0 || i == 1)
    return s[0];

  if(!isalpha(s[0]))
    return NUMBER;

  if(!strcmp(s, "prnt") || !strcmp(s, "print"))
    return PRINT;
  if(!strcmp(s, "dup") || !strcmp(s, "duplicate"))
    return DUPLICATE;
  if(!strcmp(s, "sw") || !strcmp(s, "swp") || !strcmp(s, "swap"))
    return SWAP;
  if(!strcmp(s, "clr") || !strcmp(s, "clear"))
    return CLEAR;
  if(!strcmp(s, "sin"))
    return SIN;
  if(!strcmp(s, "exp"))
    return EXP;
  if(!strcmp(s, "pow"))
    return POW;
}

#define BUFFSIZE 100

char cbuf[BUFFSIZE];
int cbufp = 0;

int getch(void) {
  return (cbufp > 0) ? cbuf[--cbufp] : getchar();
}

void ungetch(int c) {
  if(cbufp >= BUFFSIZE)
    printf("ungetch: too many characters\n");
  else
    cbuf[cbufp++] = c;
}
