#include <stdio.h>

#define ALLOCSIZE 10000
char allocbuf[ALLOCSIZE];
char *allocp = allocbuf;

char *alloc(int size) {
  if(allocbuf + ALLOCSIZE - allocp >= size)
    return (allocp += size) - size;
  else
    return NULL;
}

void afree(char *p) {
  if(p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
  if(p == NULL)
    allocp = allocbuf;
}
