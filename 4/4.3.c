#include <stdio.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'

double atof(char s[]);

void push(double val);
double pop(void);
int getop(char s[]);

main() {
  int type;
  double op2;
  char s[MAXOP];

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
      case '\n':
        printf("\t%.8g\n", pop());
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

int getch(void);
void ungetch(int);

int getop(char s[]) {
  int i, c;

  while((s[0] = c = getch()) == ' ' && isspace(c));
  s[1] = '\0';
  
  i = 0;
  if(c == '-' || c == '+' || isdigit(c))
    while(isdigit(s[++i] = c = getch()));

  if(c == '.')
    while(isdigit(s[++i] = c = getch()));

  if(i != 0) {
    s[i] = '\0';
    if(c != EOF)
      ungetch(c);
  }

  if(isdigit(s[0]))
    return NUMBER;

  if(i == 0 || i == 1) {
    return s[0];
  }

  return NUMBER;
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
