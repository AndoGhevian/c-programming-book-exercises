enum optypes {
  UNKNOWN_OP,
  NUMPUSH,
  VAROP,
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
