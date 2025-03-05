/*
  make sure those are greater than max('z', '9')
  for any character set.
*/
#define NUMBER 'z' + '9'
#define PRINT 'z' + '9' + 1
#define DUPLICATE 'z' + '9' + 2
#define SWAP 'z' + '9' + 3
#define CLEAR 'z' + '9' + 4
#define SIN 'z' + '9' + 5
#define EXP 'z' + '9' + 6
#define POW 'z' + '9' + 7
#define VAR 'z' + '9' + 8

double atof(char s[]);

int getop(char s[]);

void push(double val);
double pop(void);
void print(void);
void clear(void);

void ungetch(int c);
int getch(void);

int getch_many(void);
void ungetch_many(int c);
void ungets(char s[]);

