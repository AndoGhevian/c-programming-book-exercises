#ifndef CALCERR_H
#define CALCERR_H

enum calc_errors {
  INVALID_FLOAT,
  INVALID_VAR,
  INVALID_VAR_POSTFIX_OP,
  UNKNOWN_VAR_POSTFIX_OP,
  INVALID_CALC_OP,
  INVALID_VAR_IN_OP,
  INVALID_OP_EXTRA_PART,
  UNKNOWN_CALC_OP,
  NOT_IMPLEMENTED_CALC_OP
};

void push_calcerr(enum calc_errors t);
char *pop_calcerr(void);
int has_calcerr(void);

#endif
