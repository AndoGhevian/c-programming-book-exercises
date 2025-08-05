#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1024

void error(char *fmt, ...);

main(int argc, char *argv[]) {
  static char buf[BUFSIZE];
  int f1, f2;
  int nread;

  if(argc != 3)
    error("cp: usage, must have from, to arguments provided.");
  else if((f1 = open(argv[1], O_RDONLY, 0)) == -1)
    error("cp: can not open file %s.", argv[1]);
  else if((f2 = creat(argv[2], 0666)) == -1)
    error("cp: unable to write file %s.", argv[2]);

  while((nread = read(f1, buf, BUFSIZE)) > 0)
    if(write(f2, buf, nread) != nread)
      error("cp: error when writing a file %s.", argv[2]);

  return 0;
}

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void error(char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  fprintf(stderr, "error ");
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  va_end(ap);
  exit(1);
}
