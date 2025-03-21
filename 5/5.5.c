#include <stdio.h>

char *strncpystd(char *s, const char *ct, int n);
char *strncat(char *s, const char *ct, int n);
char *strncat(char *s, const char *ct, int n);
int strncmp(const char *cs, const char *ct, int n);

main() {
  int i;
  char s1[100] = "abc";
  char *pstr = "hh";
  s1[5] = '\65';


  printf("original: %s, ", s1);
  printf("strncpystd with 0 fill: %s\n", strncpystd(s1, "hh", 3));

  for(i = 0; i < 7; i++)
    putchar(s1[i] == '\0' ? '0' : s1[i]);
  putchar('\n');

  char s2[100] = "abc";
  pstr = "hello";
  printf("\nstrncat: %s\n", strncat(s2, pstr, 0));

  char *pstr1 = "AaBCD", *pstr2 = "ABC";
  int n = 6;
  printf("\nstrncmp: %s == %s (n=%d) %d\n", pstr1, pstr2, n, strncmp(pstr1, pstr2, n));
  printf("");

  return 0;
}

int strncmp(const char *cs, const char *ct, int n) {
  int i;

  for(i = 0; cs[i] == ct[i]; i++)
    if(cs[i] == '\0' || i == n - 1)
      return 0;

  return cs[i] - ct[i];
}

char *strncat(char *s, const char *ct, int n) {
  char *ss = s;
  int i;

  while(*s) s++;

  for(i = 0; i < n && ct[i]; i++)
    *s++ = ct[i];
  *s = '\0';

  return ss;
}

char *strncpy(char *s, const char *ct, int n) {
  int i;
  for(i = 0; i < n && (s[i] = ct[i]); i++);

  return s;
}

/* works same way as standard library version. */
char *strncpystd(char *s, const char *ct, int n) {
  int i;

  for(i = 0; i < n && (s[i] = ct[i]); i++);
  while(++i < n)
    s[i] = '\0';

  return s;
}
