#include <stdio.h>
#include <ctype.h>

void expand(char s1[], char s2[]);

main() {
  char s1[100] = "a-b-b-A-B-e--gg-z11--1-3-3-3-3-4"; /* \n-\t..-.\t */
  char s2[100];

  expand(s1, s2);
  printf("original string: %s\n", s1);
  printf("expanded: %s\n", s2);

  return 0;
}

int alphanumtype(int c);
int isrange(int rangestart, int rangeend);

void expand(char s1[], char s2[]) {
  int i, j, k;
  int c, rsc, isrs;

  for(i = 0, isrs = 0; s1[i] != '\0'; i++) {
    c = s1[i];
    if(alphanumtype(c) != 'o') {
      if(isrs)
        s2[j++] = rsc;

      rsc = c;
      isrs = 1;
    } else {
      if(isrs && c == '-' && isrange(rsc, s1[i + 1])) {
        if(rsc != s1[i + 1])
          s2[j++] = rsc;
        for(k = 1; rsc + k < s1[i + 1]; k++)
          s2[j++] = rsc + k;
      } else {
        if(isrs)
          s2[j++] = rsc;
        s2[j++] = c;
      }

      isrs = 0;
    }
  }

  if(isrs)
    s2[j++] = rsc;
  s2[j] = '\0';
}

/*
  returns character type:
  u - uppercase,
  l - lowercase,
  d - digit,
  o - other
 */
int alphanumtype(int c) {
  if(isupper(c))
    return 'u';
  if(islower(c))
    return 'l';
  if(isdigit(c))
    return 'd';
  return 'o';
}

int isrange(int rs, int re) {
  int rt = alphanumtype(rs);
  
  if(rt != 'o' && alphanumtype(re) == rt && re >= rs)
    return 1;
  return 0;
}
