#include <stdio.h>
#include <string.h>

int strindex(char s[], char right_pattern[]);

main() {
  int i, ps;
  char s[100] = "a42bcd42ef14223abc4256zxcvb";
  char t[100] = "42";

  ps = strindex(s, t);

  printf("string: %s\n", s);
  if(ps >= 0) {
    printf("pattern %s found at %d from right => ", s, ps);
    for(i = ps; s[i] != 0; i++)
      putchar(s[i]);
    putchar('\n');
  }
  else
    printf("patten %s not found\n", t);

  return 0;
}

int strindex(char s[], char t[]) {
  int i, j, k;

  i = j = 0;
  for(i = strlen(s), j = strlen(s) - strlen(t); j >= 0; i--, j--) {
    for(k = j; k < i; k++)
      if(t[k - j] != s[k])
        break;
    if(k == i)
      return j;
  }
  return -1;
}
