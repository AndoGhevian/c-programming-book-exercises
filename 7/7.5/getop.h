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
  PRINTVAR
};

enum optypes getop(char *, int *);
