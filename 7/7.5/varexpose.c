#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "varexpose.h"
#include "util.h"

/* stack data structure */
static void free_varnode(struct varexpose *);
static struct varexpose *push_varnode(struct varexpose *, int, enum expose_types);

#define MAXVAREXP 100
static char varexp[MAXVAREXP + 1];
static char spreadexp[MAXVAREXP + 1];

/* currently supported variable exposure configuration format:
    note: this function only parse and gives you asignment list,
    which you need to use to assign variables, its not doing it
    for you.
  "&4 &1 &1 &6 &4 ...&16 &11...&16 &16...&11"
  each exposure entity correspondes to next variadic argument
    - &n assign &n value to next variadic argument
    - ...&16 assign &1, &2, ... &16 to appropriately each next variadic argument
    - &11...&16 assign &11, &12, ... &16 to appropriately to each next variadic argument
    - &16...&11 (reversed assignment) &16, &15, ... &11 to each next variadic argument

  variable exposure entity can repeat for the same variable
 */
struct varexpose *parse_varexposeconfig(char const *conf) {
  struct varexpose *varstack = NULL, *varnode = NULL;
  int iserror = 0;
  int ivar_start, ivar_end, i, n;
  char *varexpptr, *ptr;

  char const *varexpendptr = varexp + MAXVAREXP;
  
  fillzero(spreadexp, MAXVAREXP + 1);
  varexp_errno = OK_VAR_EXPOSE;
  varexp_errstr = varexp_err_messages[OK_VAR_EXPOSE];

  for(ptr = conf, varexpptr = varexp; *ptr != '\0'; varexpptr = varexp) {
    while(isspace(*ptr)) ptr++;

    while(*ptr != '\0' && !isspace(*ptr) && varexpptr != varexpendptr)
      *varexpptr++ = *ptr++;
    *varexpptr = '\0';

    ivar_start = 1;
    if((n = sscanf(varexp, "&%d""%"tostrliteral(MAXVAREXP)"c", &ivar_start, spreadexp)) == EOF || ivar_start <= 0) {
      varexp_errno = INVALID_VAR_EXPOSE_CONFIG;
      break;
    }
    else if(n == 1)
      varstack = varnode = push_varnode(varstack, ivar_start, EXPOSE_FLOAT);
    else if(sscanf(n == 2 ? spreadexp : varexp, "...&%d", &ivar_end) == 1 && ivar_end > 0)
      if(ivar_end > ivar_start) {
        for(; ivar_start <= ivar_end; varstack = varnode)
          if(varexp_errno = ((varnode = push_varnode(varstack, ivar_start++, EXPOSE_FLOAT)) == NULL) * UNABLE_ALLOCATE_VAR_EXPOSE_MEMORY)
            break;
      } else {
        for(; ivar_start >= ivar_end; varstack = varnode)
          if(varexp_errno = ((varnode = push_varnode(varstack, ivar_start--, EXPOSE_FLOAT)) == NULL) * UNABLE_ALLOCATE_VAR_EXPOSE_MEMORY)
            break;
      }
    else {
      varexp_errno = INVALID_VAR_RANGE_EXPOSE_END_CONFIG;
      break;
    }

    if(varexp_errno)
      break;
  }

  if(varexp_errno) {
    free_varnode(varstack);
    varstack = varnode = NULL;
  }

  switch(varexp_errno) {
    case INVALID_VAR_EXPOSE_CONFIG:
      varexp_errstr = varexp_err_messages[INVALID_VAR_EXPOSE_CONFIG];
      break;
    case INVALID_VAR_RANGE_EXPOSE_END_CONFIG:
      varexp_errstr = varexp_err_messages[INVALID_VAR_RANGE_EXPOSE_END_CONFIG];
    case UNABLE_ALLOCATE_VAR_EXPOSE_MEMORY:
      varexp_errstr = varexp_err_messages[UNABLE_ALLOCATE_VAR_EXPOSE_MEMORY];
    case OK_VAR_EXPOSE:
      varexp_errstr = varexp_err_messages[OK_VAR_EXPOSE];
    default:
      varexp_errstr = "no message";
      break;
  }

  if(varstack == NULL)
    return NULL;

  return reverse_stack(varstack, (char *)&varstack->next - (char *)varstack);
}

#include <stdlib.h>

static struct varexpose *push_varnode(struct varexpose *node, int ivar, enum expose_types tvar) {
  struct varexpose *tailnode;
  if((tailnode = malloc(sizeof(struct varexpose))) != NULL) {
    tailnode->next = node;
    tailnode->type = tvar;
    tailnode->i = ivar;
  }
  return tailnode;
}

static void free_varnode(struct varexpose *node) {
  if(node == NULL)
    return;
  free_varnode(node->next);
  free(node);
}
