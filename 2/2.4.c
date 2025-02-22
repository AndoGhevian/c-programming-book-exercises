#include <stdio.h>

void squeeze(char s1[], char s2[]);

main() {
  char s[100] = "1222334445566677aaaAAAb";
  /* char s[100] = "113311s13123a"; */
  char sqs[100] = "11a13s2a";

  squeeze(s, sqs);

  printf("%s\n", s);
  
  return 0;
}

int find_char_index(char s[], char c);

void squeeze(char s1[], char s2[]) {
  int i, j, k, ci;

  i = 0;
  while(s1[i] != '\0') {
    ci = find_char_index(s2, s1[i]);
    if(ci != -1)
    {
      for(k = j = i; (s1[k] = s1[j]) != '\0'; ++j)
        if(s1[k] != s2[ci])
          ++k;
    }
    else
      ++i;
  }
}

int find_char_index(char s[], char c) {
  int i;

  for(i = 0; s[i] != '\0'; ++i)
    if(s[i] == c)
      return i;
  return -1;
}
