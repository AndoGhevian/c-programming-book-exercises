#include <stdio.h>
#include <string.h>
#include "../utils/bit_utils.h"

int invert(int x, unsigned int p, unsigned int n);
int setbits(int x, unsigned int p, unsigned int n, int y);
int rightrot(int x, unsigned int n);

main() {
  int x, sx;
  char xbits[100], sxbits[100];

  x = -1;
  getbinarystr(xbits, x);
  printf("bits:    \t%s\n", xbits);

  sx = setbits(x, 6, 3, 2);
  getbinarystr(sxbits, sx);
  printf("set bits:\t%s\n", sxbits);

  sx = invert(sx, 6, 3);
  getbinarystr(sxbits, sx);
  printf("invert bits:\t%s\n", sxbits);

  sx = setbits(x, 6, 3, 2);
  getbinarystr(sxbits, sx);
  printf("invert bits:\t%s\n", sxbits);
  sx = rightrot(sx, 8);
  getbinarystr(sxbits, sx);
  printf("rightrot bits:\t%s\n", sxbits);

  return 0;
}

int rightrot(int x, unsigned n) {
  unsigned int msb = ~((~0u << 1) >> 1);
  unsigned int ux = x;
  int i;
  
  for(i = 0; i < n; ++i) {
    if(ux & 1u)
      ux = ((ux >> 1) | msb);
    else
      ux = (ux >> 1);
  }

  return ux;
}

int setbits(int x, unsigned int p, unsigned int n, int y) {
  int mx = x & ~(~(~0u << n) << (p + 1 - n));
  int my = y & ~(~0u << n);

  return mx | (my << (p + 1 - n));
}

int invert(int x, unsigned int p, unsigned int n) {
  return x ^ (~(~0u << n) << (p + 1 - n));
}
