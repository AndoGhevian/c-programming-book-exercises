#include "str_utils.h"

void reverse(char s[]) {
  int c, i, len;

  for(len = 0; s[len] != '\0'; ++len);

  for(i = 0; i < len / 2; ++i) {
    c = s[i];
    s[i] = s[len - 1 - i];
    s[len - 1 - i] = c;
  }
}
