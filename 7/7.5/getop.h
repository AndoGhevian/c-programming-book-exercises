enum optypes {
  UNKNOWN_OP,
  NUMPUSH,
  VAROP,
  VARASSIGN,
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
