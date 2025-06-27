#include <stdio.h>
#include "util.h"

#define memberbyoffset(structptr, offset) ((void *)((char *)structptr + offset))

/* this function modify stack so that
  its nodes point each other in opposite
  direction, and returns new stack top,
  which is the last node in the initial stack.

  usage note: stack should be a structure which
  has member at provided offset of type void *
  pointing to next node in stack.
 */
void *reverse_stack(void *stack, int nextoffsetbytes) {
  void *lastnode, *next;

  next = *(void **)memberbyoffset(stack, nextoffsetbytes);
  lastnode = stack;
  if(next != NULL) {
    lastnode = reverse_stack(next, nextoffsetbytes);
    *(void **)memberbyoffset(next, nextoffsetbytes) = stack;
  }

  *(void **)memberbyoffset(stack, nextoffsetbytes) = NULL;
  return lastnode;
}
