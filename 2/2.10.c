#include <stdio.h>

void printarr(char arr[], int length, int numbers_per_line);
char lower(char c);

main() {
  char s[11] = "1234567891";
  char c = 'J';

  printarr(s, 10, 6);
  
  printf("char %c : lower %c .\n", c, lower(c));
  
  return 0;
}

char lower(char c) {
  return (c >= 'A' && c <= 'Z') ? 'a' + c - 'A' : c;
}

void printarr(char arr[], int l, int npl) {
  int i;
  
  for(i = 0; i < l; ++i)
    printf("%c%c", arr[i], (i % npl == npl - 1 || i == l - 1) ? '\n' : ' ');
}
