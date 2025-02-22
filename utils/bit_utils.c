#include <stdio.h>
#include "bit_utils.h"

void getbinarystr(char b[], unsigned int n) {
  int len = 0;

  len = 0;
  while(n != 0) {
    b[len++] = (n & 1u) + '0';
    n = n >> 1;
  }
  b[len] = '\0';

  reverse(b);

  fill_int_right_bits(b);
}

void fill_int_right_bits(char b[]) {
  short isize = int_size();
  int i, len;

  for(len = 0; b[len] != '\0'; ++len);

  for(i = isize - 1; i >= isize - len; --i)
    b[i] = b[i - (isize - len)];
  b[i] = '\0';

  for(i = 0; i < isize - len; ++i)
    b[i] = '0';
}

unsigned int get_sign(int n) {
  unsigned int ui = n;
  int i;

  for(i = 1; i < int_size(); ++i)
    ui = ui >> 1;

  return ui == 1;
}

short int int_size() {
  short int i = 1;
  unsigned int n = 01;

  while((n = (n << 1)) != 0)
    ++i;
  return i;
}

void reverse(char s[]) {
  int c, i, len;

  for(len = 0; s[len] != '\0'; ++len);

  for(i = 0; i < len / 2; ++i) {
    c = s[i];
    s[i] = s[len - 1 - i];
    s[len - 1 - i] = c;
  }
}
