#include <stdio.h>
#include <stdlib.h>
#include "vartable.h"
#include "printvars.h"

struct printvar {
  int var_start;
  int var_end;
  int spread;
  struct printvar *next;
} *printsequence;

void push_printvarrange(int var_start, int var_end) {
  struct printvar *printnode;
  printnode = malloc(sizeof(struct printvar));
  if(printnode == NULL)
    return;
  printnode->next = printsequence;
  printsequence = printnode;
  printnode->spread = 0;
  printnode->var_start = var_start;
  printnode->var_end = var_end;
}

void push_printvarspread(void) {
  struct printvar *printnode;
  printnode = malloc(sizeof(struct printvar));
  if(printnode == NULL)
    return;
  printnode->next = printsequence;
  printsequence = printnode;
  printnode->spread = 1;
}

void push_printvar(int var) {
  struct printvar *printnode;
  printnode = malloc(sizeof(struct printvar));
  if(printnode == NULL)
    return;
  printnode->next = printsequence;
  printsequence = printnode;
  printnode->var_end = printnode->var_start = var;
  printnode->spread = 0;
}

void flushprintvars(void) {
  int i, doesprint;
  struct printvar *clearnode, *printnode;

  doesprint = printsequence != NULL;
  for(printnode = printsequence;
    printnode != NULL;
    clearnode = printnode, printnode = printnode->next, free(clearnode)
  )
    if(!printnode->spread)
      if(printnode->var_start <= printnode->var_end)
        for(i = printnode->var_start; i <= printnode->var_end; i++)
          printf("%.4g ", lookupvar(i));
      else
        for(i = printnode->var_start; i >= printnode->var_end; i--)
          printf("%.4g ", lookupvar(i));
    else
      for(i = scanvar(-1); i > 0; i = scanvar(i))
        printf("&%d=%.4g ", i, lookupvar(i));
  printsequence = NULL;

  if(doesprint)
    putchar('\n');
}
