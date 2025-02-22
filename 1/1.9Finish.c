#include <stdio.h>

#define MAXLINE 100

void reverse(char s[]);

main() {
  int c, i;
  char line[MAXLINE];
  
  i = 0;
  while((c = getchar()) != EOF) {
    if(c == '\n') {
      line[i] = '\0';
      
      reverse(line);
      if(i != 0)
        printf("%s\n", line);
      i = 0;
    } else {
      line[i] = c;
      ++i;
    }
  }
  
  return 0;
}


void reverse(char s[]) {
  int c, i, len;

  for(i = 0; s[i] != '\0'; ++i);
  len = i;

  for(i = 0; i < len / 2; i++) {
    c = s[i];
    s[i] = s[len - 1 - i];
    s[len - 1 - i] = c;
  }
}


/* #include <stdio.h>

#define MAXPRESENTATIONLENGTH 4
#define MAXSTRINGS 10
#define MINLENGTH 8

int get_line(char line[], int maxline);
int appendline(char to[], char line[], int lim);

main() {
  int len;
  char line[MAXPRESENTATIONLENGTH];
  char strings[MAXSTRINGS];
  strings[0] = '\0';

  while((len = get_line(line, MAXPRESENTATIONLENGTH)) != 0)
    if(len >= MINLENGTH)
      appendline(strings, line, MAXSTRINGS);

  printf("\nLines with length greater than %d\n", MINLENGTH);
  printf("%s", strings);

  return 0;
}

int appendline(char to[], char line[], int lim) {
  int i, starti, len;

  for(i = 0; to[i] != '\0'; ++i);
  starti = i;

  for(len = 0; line[len] != '\0'; ++len);
  if(len + starti + 1 > lim)
    return -1;
  
  for(i = starti; line[i - starti] != '\0'; ++i)
    to[i] = line[i - starti];
  to[i] = '\0';
  ++i;

  return 1;
}

int get_line(char s[], int lim) {
  int c, i, si, len;

  len = 0;
  for(i = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
    if(i < lim - 2) {
      s[i] = c;
    }
  }
  if(c == '\n')
    len = i + 1;

  if(i <= lim - 2)
    si = i;
  else
    si = lim - 2;
  
  s[si] = '\n';
  s[si + 1] = '\0';

  return len;
} */


/* 
int get_line(char s[], int lim) {
  int c, i, si;

  for(i = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
    if(i < lim - 1)
      s[i] = c;
  }
  if(c == '\n') {
    ++i;
    if(i < lim - 1)
      s[i] = c;
  }

  if(i < lim - 1)
    si = i;
  else
    si = lim - 1;

  s[si] = '\0';

  return i;
}

void copy(char to[], char from[]) {
  int i;

  i = 0;
  while((to[i] = from[i]) != '\0')
    ++i;
}
 */