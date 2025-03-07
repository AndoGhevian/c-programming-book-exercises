#include <stdio.h>
#define swap(t, x, y) {t temp = x; x = y; y = temp;} /* as if it's return value is void */

main() {
  int x, y;
  x = 100;
  y = 19;

  printf("x=%d, y=%d\n", x, y);
  swap(int, x, y);
  printf("x=%d, y=%d\n", x, y);

  return 0;
}
