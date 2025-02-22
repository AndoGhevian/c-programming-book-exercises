/* Not Finished: Computiton part */
#include <stdio.h>
#include <limits.h>

main() {
  printf("%15s\t", "");
  printf("%20s\t%20s\n", "Min", "Max");

  printf("%15s\t", "Char");
  printf("%20d\t%20d\n", SCHAR_MAX, CHAR_MAX);

  printf("%15s\t", "Signed Char");
  printf("%20d\t%20d\n", SCHAR_MIN, SCHAR_MAX);

  printf("%15s\t", "Unsigned Char");
  printf("%20d\t%20d\n", 0, UCHAR_MAX);

  printf("%15s\t", "Short");
  printf("%20d\t%20d\n", SHRT_MIN, SHRT_MAX);

  printf("%15s\t", "Signed Short");
  printf("%20d\t%20d\n", SHRT_MIN, SHRT_MAX);

  printf("%15s\t", "Unsigned Short");
  printf("%20d\t%20d\n", 0, USHRT_MAX);

  printf("%15s\t", "Int");
  printf("%20d\t%20d\n", INT_MIN, INT_MAX);

  printf("%15s\t", "Signed Int");
  printf("%20d\t%20d\n", INT_MIN, INT_MAX);

  printf("%15s\t", "Unsigned Int");
  printf("%20d\t%20u\n", 0, UINT_MAX);

  printf("%15s\t", "Long");
  printf("%20ld\t%20ld\n", LONG_MIN, LONG_MAX);

  printf("%15s\t", "Signed Long");
  printf("%20ld\t%20ld\n", LONG_MIN, LONG_MAX);

  printf("%15s\t", "Unsigned Long");
  printf("%20d\t%20lu\n", 0, ULONG_MAX);
  
  return 0;
}
