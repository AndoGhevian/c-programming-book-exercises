#include <stdio.h>
#include <string.h>
#include "keyval.h"

struct keyval *binsrch_keyval(char *s, struct keyval *v, int n) {
  int comp;

  struct keyval *mid;
  struct keyval *left = v;
  struct keyval *right = &v[n];

  while(left < right)
    if((comp = strcmp(s, (mid = left + (right - left) / 2)->key)) < 0)
      right = mid;
    else if(comp > 0)
      left = mid + 1;
    else
      return mid;

  return NULL;
}
