#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char t[], char s[]);

main() {
  char s[100];
  char t[100] = "asda\nasdas\tasd\t";
  
  escape(s, t);
  printf("before escape: \"\"\"%s\"\"\"\n", t);
  printf("after escape: %s\n", s);

  unescape(t, s);
  printf("reverse escaped: \"\"\"%s\"\"\"\n", t);

  return 0;
}

void escape(char s[], char t[]) {
  int i, j;

  i = j = 0;
  while(t[i] != '\0') {
    switch(t[i]) {
      case '\t':
        s[j++] = '\\';
        s[j++] = 't';
        break;
      case '\n':
        s[j++] = '\\';
        s[j++] = 'n';
        break;
      default:
        s[j++] = t[i];
        break;
    }
    ++i;
  }

  s[j] = '\0';
}

void unescape(char t[], char s[]) {
  int i, j, tc;

  i = j = tc = 0;
  while(s[i] != '\0') {
    if(s[i] == '\\')
      switch(s[i + 1]) {
        case 't':
          tc = '\t';
          break;
        case 'n':
          tc = '\n';
          break;
        default:
          tc = 0;
          break;
      }

    if(tc) {
      t[j] = tc;
      i += 2;
    } else {
      t[j] = s[i];
      ++i;
    }

    ++j;
    tc = 0;
  }

  t[j] = '\0';
}
