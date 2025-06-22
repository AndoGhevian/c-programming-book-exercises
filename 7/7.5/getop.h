enum optypes {
  UNKNOWN_OP,
  NUMPUSH,
  VAR,
  VARASSIGN,
  VAROPTASSIGN,
  CLEARSTACK,
  ADD,
  MUL,
  SUBTR,
  DIV,
  ADDVAR,
  MULVAR,
  SUBTRVAR,
  DIVVAR,
  PRINT
};

/* in case if this is required outisde of getop file scope,
it will be required to be defined as a file-scope variable
because (struct op) type is not exposed to the final users.
*/
#define N_OPABBRS (sizeof opabbrs / sizeof(struct op))

enum optypes getop(char *, int *);
