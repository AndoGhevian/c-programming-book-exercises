#ifndef CALCERR_H
#define CALCERR_H

enum calc_errors {
  INVALID_FLOAT,
  INVALID_VAR,
  INVALID_VAR_POSTFIX_OP,
  UNKNOWN_VAR_POSTFIX_OP,
  INVALID_CALC_OP,
  INVALID_VAR_IN_PREFIX_OP,
  INVALID_VAR_IN_PRINT_OP,
  INVALID_OP_EXTRA_PART,
  UNKNOWN_CALC_OP,
  NOT_IMPLEMENTED_CALC_OP
};

/* if there is no storage space for new errors
they will be silently omited */
void push_calcerr(enum calc_errors t);
/*returns appropriate error message in stack
or NULL if no errors left */
char *pop_calcerr(void);
int has_calcerr(void);

#endif
