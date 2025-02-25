#include <stdio.h>
#include <limits.h>
#include "utils/str_utils.h"

int maxbase = ('9' - '0' + 1) + ('z' - 'a' + 1);

void itoa(int n, char s[]);
void itob(int n, char s[], short b);
void itoaw(int n, char s[], int w);

main() {
  int x, b, w;
  char s[100];

  x = INT_MIN;
  itoa(x, s);
  printf("number %d\nstring representation: %s\n", x, s);

  x = 35;
  b = 36;
  itob(x, s, b);
  printf("number %d\nbase %d representation: %s\n", x, b, s);

  x = 12345;
  w = 6;
  itoaw(x, s, w);
  printf("number %d\nmin width print %d: \"%s\"\n", x, w, s);
  
  return 0;
}

/*
  -2^wordsize-1 * -1 gives overflow from wordsize,
  so example itoa in the book is inappropriate.

  Here is modified, correct, machine-independent version.

  base can represent 0-9a-z => 36 digits max.
*/
void itoa(int n, char s[]) {
  unsigned int msb = ~((~0u << 1) >> 1);
  unsigned un = n;
  int i, sign;

  sign = 0;
  if(n < 0)
    sign = 1;

  i = 0;
  do {
    s[i++] = '0' + un % 10;
  } while(un /= 10);
  if(sign)
    s[i++] = '-';
  s[i] = '\0';

  reverse(s);
}

void itoaw(int n, char s[], int w) {
  unsigned int un = n;
  int i, sign;

  sign = 0;
  if(n < 0)
    sign = 1;
  
  i = 0;
  do {
    s[i++] = un % 10 + '0';
  } while(un /= 10);
  if(sign)
    s[i++] = '-';
  while(i < w)
    s[i++] = ' ';
  s[i] = '\0';
  
  reverse(s);
}

int itobc(unsigned int n, unsigned short b);

void itob(int n, char s[], short b) {
  unsigned int un = n;
  int i, sign;
  
  if(b > maxbase || b <= 1) {
    s[0] = '\0';
    return;
  }

  sign = 0;
  if(n < 0)
    sign = 1;
  
  i = 0;
  do {
    s[i++] = itobc(un % b, b);
  } while(un /= b);
  if(sign)
    s[i++] = '-';
  s[i] = '\0';

  reverse(s);
}

int itobc(unsigned int n, unsigned short b) {
  if(b > maxbase || n >= b)
    return '\0';

  if(n < 10)
    return '0' + n;
  else
    return 'a' + n - 10;
}
