#include <stdio.h>
#include <fcntl.h>

int fcpy(int, int);

void warn(char *, ...);
void error(char *, int status, ...);

char *prog = "unnamed command";
enum filecpyerrno {
  FAILRD = -100,
  FAILWR
};

int main(int argc, char *argv[]) {
  int fin, fout;
  int cpyerrno;

  if(argc >= 1 && **argv != '\0')
    prog = *argv;

  fin = 0;
  fout = 1;
  if(argc <= 1) {
    if((cpyerrno = fcpy(fin, fout)) == FAILRD)
      error("fail reading from standard input. exiting.", 2);
    else if(cpyerrno == FAILWR)
      error("fail writing to standard output. exiting.", 1);
  } else
    while(*++argv != NULL)
      if((fin = open(*argv, O_RDONLY, 0)) != -1) {
        if((cpyerrno = fcpy(fin, fout)) == FAILRD)
          warn("fail reading file %s.", *argv);
        else if(cpyerrno == FAILWR)
          error("fail to write to standard output. exiting.", 1);
        close(fin);
      } else
        warn("fail to open a file %s.", *argv);
  return 0;
}

#include <unistd.h>
#define BUFSIZE 1024

int fcpy(int fin, int fout) {
  static char buf[BUFSIZE];
  int n;

  while((n = read(fin, buf, BUFSIZE)) > 0)
    if(n != write(fout, buf, n))
      return FAILWR;
  if(n == -1)
    return FAILRD;
  return 0;
}

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

extern char *prog;

void warn(char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  fprintf(stderr, "warning %s: ", prog);
  vfprintf(stderr, fmt, ap);
  fputc('\n', stderr);
  va_end(ap);
}

void error(char *fmt, int status, ...) {
  va_list ap;

  va_start(ap, status);
  fprintf(stderr, "error %s: ", prog);
  vfprintf(stderr, fmt, ap);
  fputc('\n', stderr);
  va_end(ap);

  exit(status);
}
