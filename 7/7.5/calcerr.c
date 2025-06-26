#include <stdio.h>
#include "calcerr.h"

static char const *message_notdefined = "error message not defined";

static struct err_entity {
  enum calc_errors errtype;
  char *message;
} errmessages[] = {
  INVALID_FLOAT, "invalid float.",
  INVALID_VAR, "invalid variable (or range).",
  INVALID_NOT_POSITIVE_VAR, "invalid var index, must be positive number.",
  INVALID_VAR_POSTFIX_OP, "invalid variable postfix operation.",
  UNKNOWN_VAR_POSTFIX_OP, "unknown variable postfix operation.",
  INVALID_CALC_OP, "invalid calculator operation.",
  INVALID_VAR_IN_PREFIX_OP, "invalid variable (or range) in prefix operation.",
  INVALID_VAR_IN_PRINT_OP, "invalid variable (or range) in print operation.",
  INVALID_OP_EXTRA_PART, "invalid operation excess part.",
  UNKNOWN_CALC_OP, "unknown calculator operation.",
  NOT_IMPLEMENTED_CALC_OP, "not implemented calculator operation."
};

#define NERR sizeof errmessages / sizeof(struct err_entity)

#define MAXERR 100
int errors[MAXERR];
int *errtop = errors;

void push_calcerr(enum calc_errors t) {
  if(errtop < errors + MAXERR)
    *errtop++ = t;
}

char *pop_calcerr(void) {
  int i, t;

  if(errtop == errors)
    return NULL;

  for(i = 0, t = *--errtop; i < NERR; i++)
    if(errmessages[i].errtype == t)
      return errmessages[i].message;

  return message_notdefined;
}

int has_calcerr(void) {
  return errtop > errors;
}

void flusherrors(void) {
  char *err;

  while(err = pop_calcerr())
    printf("%s\n", err);
}
