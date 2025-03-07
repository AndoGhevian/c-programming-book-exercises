#include <stdio.h>
#include <string.h>

void reverse(char s[]);

main() {
  char s[100] = "hello world!"; /* "aBx\n"; */

  printf("string %s\n", s);
  reverse(s);
  printf("reversed %s\n", s);

  return 0;
}

void reverse(char s[]) {
  static int ri = -1;
  static int left, right;
  int tmp;
  ri++;
  if(ri == 0) {
    left = 0;
    right = strlen(s) - 1;
  }

  if(right > left) {
    tmp = s[left];
    s[left++] = s[right];
    s[right--] = tmp;
    reverse(s);
  }
  ri--;
}
