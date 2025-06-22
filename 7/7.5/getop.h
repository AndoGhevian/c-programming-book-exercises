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

enum optypes getop(char *, int *);
