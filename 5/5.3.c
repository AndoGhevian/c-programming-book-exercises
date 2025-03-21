#include <stdio.h>

char *strcat(char *s, char *t);

main() {
  char s[100] = "continue copying: ";
  char *t = "hello world!";

  printf("%s\n", strcat(s, t));

  return 0;
}

char *strcat(char *s, char *t) {
  char *ss = s;
  while(*s) s++;

  while(*s++ = *t++);

  return ss;
}
