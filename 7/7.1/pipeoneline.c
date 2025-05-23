#include <stdio.h>

main(int argc, char *argv[]) {
  int c;

  while((c = getchar()) != '\n' && c != EOF)
    putchar(c);
  putchar('\n');

  return 0;
}
