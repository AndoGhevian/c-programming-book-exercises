#include <stdio.h>

int bitcount(unsigned int x);

main() {
  int x = (int)(~((~0u << 1) >> 1));
  printf("number %u bits count: %d\n", x, bitcount(x));
  
  return 0;
}

int bitcount(unsigned int x) {
  int i;
  int msb = ~((~0u << 1) >> 1);
  
  if(x == 0)
    return 0;
  
  i = 1;
  while(x != msb && (x &= x - 1))
    ++i;

  return i;
}
