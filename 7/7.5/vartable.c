#include <stdio.h>
#include <stdlib.h>
#include "vartable.h"

static void insertvarinorder(struct var *);

#define TABGRANULARITY 1000

struct var {
  float v;
  int i;
  struct var *nextinorder;
  struct var *nextintablist;
} *vartab[TABGRANULARITY];

float lookupvar(int i) {
  struct var *varnode;
  for(varnode = vartab[i % TABGRANULARITY]; varnode != NULL; varnode = varnode->nextintablist)
    if(varnode->i == i)
      return varnode->v;
  return 0;
}

int installvar(int i, float v) {
  struct var *varnode, *newvar;

  for(varnode = vartab[i % TABGRANULARITY]; varnode != NULL; varnode = varnode->nextintablist)
    if(varnode->i == i)
      varnode->v = v;

  if(varnode)
    return 1;

  newvar = malloc(sizeof(struct var));
  if(newvar == NULL)
    return 0;

  newvar->nextintablist = vartab[i % TABGRANULARITY];
  vartab[i % TABGRANULARITY] = newvar;
  newvar->nextinorder = NULL;
  newvar->i = i;
  newvar->v = v;

  insertvarinorder(newvar);
  return 1;
}


struct var *orderedvars = NULL;

static void insertvarinorder(struct var *varnode) {
  struct var *prevnode, *curnode;

  if(orderedvars == NULL) {
    orderedvars = varnode;
    return;
  }

  for(prevnode = NULL, curnode = orderedvars;
    curnode != NULL && curnode->i < varnode->i;
    prevnode = curnode, curnode = curnode->nextinorder);
  if(prevnode)
    prevnode->nextinorder = varnode;
  varnode->nextinorder = curnode;
}

int scanvar(int i) {
  struct var *nextvar;

  nextvar = orderedvars;
  for(; nextvar != NULL && i >= nextvar->i; nextvar = nextvar->nextinorder);

  if(nextvar == NULL)
    return -1;
  return nextvar->i;
}
