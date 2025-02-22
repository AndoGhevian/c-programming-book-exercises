#include <stdio.h>

#define MAXINPUTSIZE 1000
int tabsize = 3;

int readinput(char s[], int stringlimit);
int replace_tabs(char s[], char input[], int limit);

main() {
  int i;
  char input[MAXINPUTSIZE];
  char result[MAXINPUTSIZE];

  readinput(input, MAXINPUTSIZE);
  replace_tabs(result, input, MAXINPUTSIZE);

  printf("\n%s", result);
  return 0;
}

void append_blanks(char to[], int start, int blanks_number);

int replace_tabs(char s[], char input[], int limit) {
  int c, i, nb, len;
  int allowednb;

  nb = 0;
  len = 0;
  i = 0;
  for(i = 0; input[i] != '\0' && len < limit - 1; ++i) {
    if(input[i] == '\t')
      nb = (nb / tabsize + 1) * tabsize;
    else if(input[i] == ' ')
      ++nb;
    else {
      if(nb != 0) {
        allowednb = nb;
        if(nb + len >= limit - 1)
          allowednb = limit - 2 - len;

        append_blanks(s, len, allowednb);
        len = len + allowednb;
        nb = 0;
      }
      s[len] = input[i];
      ++len;
    }
  }

  s[len] = '\0';

  return len;
}

int readinput(char inputstr[], int limit) {
  int c, i;

  for(i = 0; (c = getchar()) != EOF && i < limit - 1; ++i)
    inputstr[i] = c;

  inputstr[i] = '\0';

  return i;
}

void append_blanks(char to[], int start, int blanks_number) {
  int i;
  
  for(i = 0; i < blanks_number; ++i)
    to[i + start] = ' ';
}
