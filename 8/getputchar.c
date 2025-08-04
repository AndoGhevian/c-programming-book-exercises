#include <stdio.h>
#undef getchar
#undef putchar

main() {
  int c;

  while((c = getchar()) != EOF)
    putchar(c);

  return 0;
}

/*unix standard header, maybe*/
#include <unistd.h>
#define BUFSIZE 1024

int getchar(void) {
  static char buf[BUFSIZE];
  static char *bufp = buf;
  static int n = 0;

  if(n == 0) {
    n = read(0, buf, BUFSIZE);
    bufp = buf;
  }

  return --n >= 0 ? (unsigned char)*bufp++ : EOF;
}

int putchar(int c) {
  unsigned char uc = c;
  char *cbyte = &uc;

  if(c < 0)
    return EOF;

  /* write expects char pointer
    so we make explicit conversion,
    even though void * has same
    representation and alignment
    as a char pointer.
  */
  return write(1, cbyte, 1) > 0 ? c : EOF;
}
 