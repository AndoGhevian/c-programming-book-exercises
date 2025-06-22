#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "varexpose.h"
#include "var.h"
#include "util.h"

/* stack data structure */
static void free_varnode(struct varexpose *);
static struct varexpose *push_varnode(struct varexpose *, int, enum expose_types);

#define MAXVAREXP 100
static char varexp[MAXVAREXP + 1];
static char dummystr[MAXVAREXP + 1];

/* currently supported variable exposure configuration format:
    note: this function only parse and gives you assignment list,
    which you need to use to assign variables, its not doing it
    for you.
  "&4 &1 &1 &6 &4 ...&16 &11...&16 &16...&11"
  each exposure entity correspondes to next variadic argument
    - &n assign &n value to next variadic argument
    - ...&16 assign &1, &2, ... &16 to appropriately each next variadic argument
    - &11...&16 assign &11, &12, ... &16 to appropriately to each next variadic argument
    - &16...&11 (reversed assignment) &16, &15, ... &11 to each next variadic argument

  variable exposure entity can repeat for the same variable
  entities are need to be separated by spaces.
 */
struct varexpose *parse_varexposeconfig(char const *conf) {
  struct varexpose *varstack = NULL, *varnode = NULL;
  int iserror = 0;
  int ivar_start, ivar_end, i, n;
  char *varexpptr, *ptr;
  enum var_entities tvar;

  char const *varexpendptr = varexp + MAXVAREXP;
  
  varexp_errno = OK_VAR_EXPOSE;
  varexp_errstr = varexp_err_messages[OK_VAR_EXPOSE];

  for(ptr = conf, varexpptr = varexp; *ptr != '\0'; varexpptr = varexp) {
    while(isspace(*ptr)) ptr++;

    while(*ptr != '\0' && !isspace(*ptr) && varexpptr != varexpendptr)
      *varexpptr++ = *ptr++;
    *varexpptr = '\0';

    ivar_start = 1;
    tvar = parse_varstr(varexp, &ivar_start, &ivar_end, dummystr);
    if(tvar == INVALID_VAR || *dummystr != '\0')
      varexp_errno = INVALID_VAR_EXPOSE_CONFIG;
    else
      switch(tvar) {
        case SINGLE_VAR:
          if(ivar_start <= 0) {
            varexp_errno = INVALID_VAR_SINGLE_EXPOSE;
            break;
          }

          varstack = varnode = push_varnode(varstack, ivar_start, EXPOSE_FLOAT);
          break;
        case VAR_RANGE:
          if(ivar_start <= 0 || ivar_end <= 0) {
            if(ivar_start <= 0 && ivar_end <= 0)
              varexp_errno = INVALID_VAR_RANGE_EXPOSE_START_AND_END;
            else if(ivar_start <= 0)
              varexp_errno = INVALID_VAR_RANGE_EXPOSE_START;
            else
              varexp_errno = INVALID_VAR_RANGE_EXPOSE_END;
            break;
          }

          if(ivar_end > ivar_start) {
            for(; ivar_start <= ivar_end; varstack = varnode)
              if(varexp_errno = (
                (varnode = push_varnode(varstack, ivar_start++, EXPOSE_FLOAT)) == NULL
              ) * UNABLE_ALLOCATE_VAR_EXPOSE_MEMORY)
                break;
          } else {
            for(; ivar_start >= ivar_end; varstack = varnode)
              if(varexp_errno = (
                (varnode = push_varnode(varstack, ivar_start--, EXPOSE_FLOAT)) == NULL
            ) * UNABLE_ALLOCATE_VAR_EXPOSE_MEMORY)
                break;
          }
          break;
        default:
          varexp_errno = INVALID_VAR_EXPOSE_CONFIG;
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
    case INVALID_VAR_SINGLE_EXPOSE:
    case INVALID_VAR_RANGE_EXPOSE_START_AND_END:
    case INVALID_VAR_RANGE_EXPOSE_START:
    case INVALID_VAR_RANGE_EXPOSE_END:
    case UNABLE_ALLOCATE_VAR_EXPOSE_MEMORY:
      varexp_errstr = varexp_err_messages[varexp_errno];
      break;
    case OK_VAR_EXPOSE:
      varexp_errstr = varexp_err_messages[OK_VAR_EXPOSE];
      break;
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
