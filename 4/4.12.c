#include <stdio.h>
#include <ctype.h>
#include <limits.h>

void itoa(char s[], int i);

main() {
  char s[100];
  int i = -2173612;
  /* i = INT_MIN; */

  itoa(s, i);
  printf("number %d\nnumber string: %s\n", i, s);
  
  return 0;
}

void itoa(char s[], int i) {
  /* printf("my implementation log"); */
  static int ri = -1;
  static int ni = 0;
  unsigned int ui = i == INT_MIN ? INT_MAX + 1u : i < 0 ? -i : i;

  ri++; /* recursion call stack index */
  if(ri == 0)
    ni = 0;

  if(ri == 0 && i < 0)
    s[ni++] = '-';

  if(ui / 10)
    itoa(s, ui / 10);
  s[ni++] = ui % 10 + '0';
  ri--;
}
