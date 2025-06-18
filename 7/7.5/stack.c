#include <stdio.h>

static void *lastnode;

/* this function modify stack so that
  its nodes point each other in opposite
  direction, and returns new stack top,
  which is the last node in the initial stack.

  usage note: stack should be a structure which
  has first member of type void * pointing to
  next node in stack.
 */
void *reverse_stack(void *stack) {
  void *lastnode, *next;

  next = *(void **)stack;
  lastnode = stack;
  if(next != NULL) {
    lastnode = reverse_stack(next);
    *(void **)next = stack;
  }

  *(void **)stack = NULL;
  return lastnode;
}
