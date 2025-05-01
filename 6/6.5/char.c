/*design considerations:
  there are 2 main ways to implement getch
  with support of different sources.
  1. single source support throught sequential
    calls.
  2. multy source support for paralell calls.

  in both cases it is crucial to perform flush
  of a buffer from caller side if input
  is not exhausted:
  1. to not produce invalid values if
    the pointer is reallocated on the caller side.
  2. to not introduce memory leaks if multiple
    inputs states are stored in the buffer.
  NOTE: We will get undefined behaviour
    when performing any operation on invalid pointer
    as stated in ANSI C Rational 3.2.2.3

  this should be considered always when a function is
  storing some cache based on a pointer provided
  from outside, caller MUST be able to free internal
  cache of a callee before it can reallocate or free
  a pointer.

  we use for this porpouse flushbuf function
  to erase internal state related to that particular
  pointer, before we even free it.
  */

#include <stdio.h>
#include "char.h"

#define EMPTYCHAR EOF - 1

struct chbuffer {
  char *input;
  char *lastcptr;
  char c;
};

static struct chbuffer buf = {
  NULL, NULL, EMPTYCHAR
};

struct chbuffer *addbuf(char *, char c);
void flushbuf(char *);

int getch(char *input) {

}
