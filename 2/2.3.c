#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


#define LINELIM 4

int htol(char s[]);

main() {
  char s[] = "0x123Af";
  

  printf("%d\n", htol(s));
}

int gethexchar(char character);

int htol(char s[]) {
  int c, i, st, rs, ad;
  int len = strlen(s);

  st = 0;
  if(s[0] != '\0' && s[1] != '\0')
    if(s[0] == '0' && tolower(s[1]) == 'x')
      st = 2;

  if(gethexchar(st) == -1)
    return -1;

  c = 0;
  rs = 0;
  for(i = st; s[i] != '\0' && (c = gethexchar(s[i])) != -1; ++i) {
    if(isdigit(c))
      ad = c - '0';
    else
      ad = tolower(c) - 'a' + 10;
    rs = rs + ad * (int)pow(16, len - i - 1);
  }

  return rs;
}

int gethexchar(char c) {
  char lowerc = tolower(c);
  
  if(isdigit(c))
    return c;

  if(lowerc >= 'a' || lowerc <= 'f')
    return c;

  return -1;
}
