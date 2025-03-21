#include <stdio.h>

char *strcat(char *s, char *t);
int strend(char *s, char *t);

main() {
  char s[100] = "continue copying: ";
  char *t = "hello world!";

  printf("%s\n", strcat(s, t));

  char *ss = "hello world!";
  char *ts = "lo world!";

  printf("%d\n", strend(ss, ts));

  return 0;
}

char *strcat(char *s, char *t) {
  char *ss = s;
  while(*s) s++;

  while(*s++ = *t++);

  return ss;
}

int strend(char *s, char *t) {
  char *ss = s;
  char *ts = t;

  while(*s) s++;
  while(*t) t++;

  while(t > ts && s > ss && *s-- == *t--)
    if(*s != *t)
      return 0;
  return t == ts && s >= ss && *s == *t;
}
