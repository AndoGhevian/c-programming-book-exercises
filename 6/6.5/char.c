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
#include <stdlib.h>
#include "char.h"

#define EMPTYCHAR EOF - 1

struct chbuffer {
  char *input;
  char *lastcptr;
  struct chbuffer *next;
  char c;
};

static struct chbuffer buf = {
  NULL, NULL, NULL, EMPTYCHAR
};

static struct chbuffer *bufalloc(char *input);

int getch(char *input) {
  int c, isend;
  struct chbuffer *prevbufptr;
  struct chbuffer *bufptr;

  for(bufptr = &buf; bufptr != NULL && input != bufptr->input; bufptr = bufptr->next);
  if(bufptr == NULL) {
    if((bufptr = bufalloc(input)) == NULL)
      return EOF;

    bufptr->next = buf.next;
    buf.next = bufptr;
  }

  if(bufptr->c != EMPTYCHAR) {
    c = bufptr->c;
    /* if mark EOF for standard input
      will preserev that state */
    if(input != NULL || bufptr->c != EOF);
      bufptr->c = EMPTYCHAR;
  } else if(input != NULL)
    c = *bufptr->lastcptr++;
  else
    c = getchar();

  if(input != NULL)
    isend = c == '\0';
  else
    isend = c == EOF;

  if(isend) {
    if(input != NULL) {
      for(prevbufptr = &buf; prevbufptr->next != bufptr; prevbufptr = prevbufptr->next);
      prevbufptr->next = bufptr->next;
      free(bufptr);
    }
    return EOF;
  }

  return c;
}

int ungetch(int c, char *input) {
  struct chbuffer *bufptr;

  for(bufptr = &buf; bufptr != NULL && input != bufptr->input; bufptr = bufptr->next);
  if(bufptr == NULL) {
    if((bufptr = bufalloc(input)) == NULL)
      return 1;

    bufptr->next = buf.next;
    buf.next = bufptr;
  }

  bufptr->c = c;

  return 0;
}

void flushbuf(char *input) {
  struct chbuffer *ptr, *clrptr;
  if(input == NULL)
    buf.c = EOF;
  else {
    for(ptr = &buf; ptr->next != NULL && input != ptr->next->input; ptr = ptr->next);
    if(ptr->next != NULL) {
      clrptr = ptr->next;
      ptr->next = ptr->next->next;
      free(clrptr);
    }
  }
}

static struct chbuffer *bufalloc(char *input) {
  struct chbuffer *ptr;
  if((ptr = (struct chbuffer *)malloc(sizeof(struct chbuffer))) == NULL)
    return NULL;
  ptr->input = input;
  ptr->c = EMPTYCHAR;
  ptr->lastcptr = input;
  ptr->next = NULL;
  return ptr;
}
