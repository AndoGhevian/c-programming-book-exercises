#ifndef UTIL_H
#define UTIL_H

#define tostrliteral_helper(V) #V
#define tostrliteral(value) tostrliteral_helper(value)

void *reverse_stack(void *stack, int nextoffsetbytes);

/* here we define a global variable
instead of symbolic name to not allocate
each time an empty string (1 character array '\0').
*/
char const *RESET_GETCH = "";

/* NULL to read from standard input.
to reset reading you need to pass RESET.
RESET simply an empty string defined in
util header. otherwise after EOF all
subseqent calls will return EOF unitl reset.

note: in fact, you can pass any other src,
than for initial call, and then repass the same src.
the reason we use empty string, is because in effect
it will hit '\0' and so EOF will be returned as
a natural subseqent value, and no value will be lost.
*/
int getch(char *);

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

#define MAXABBR 10

struct op {
  enum optypes type;
  char *abbr[MAXABBR];
  int abbrlen[MAXABBR];
} opabbrs[] = {
  /* ops without abbreviations can be omited */
  { NUMPUSH, {NULL} },
  { VAR, {NULL} },

  { VARASSIGN, {"=", NULL}, {sizeof("=") - 1} },
  { VAROPTASSIGN, {"=?", NULL}, {sizeof("=?") - 1} },
  /* compile time abbreviations and their length defined */
  { CLEARSTACK, {"clear", "clr", NULL}, {sizeof("clear") - 1, sizeof("clr") - 1} },
  { ADD, {"+", NULL}, {sizeof("+") - 1} },
  { MUL, {"*", NULL}, {sizeof("*") - 1} },
  { SUBTR, {"-", NULL}, {sizeof("-") - 1} },
  { DIV, {"/", NULL}, {sizeof("/") - 1} },
  { ADDVAR, {"+&", NULL}, {sizeof("+&") - 1} },
  { MULVAR, {"*&", NULL}, {sizeof("*&") - 1} },
  { SUBTRVAR, {"-&", NULL}, {sizeof("-&") - 1} },
  { DIVVAR, {"/&", NULL}, {sizeof("/&") - 1} },
  { PRINT, {"print", NULL}, {sizeof("print") - 1} }
};

#define N_OPABBRS (sizeof opabbrs / sizeof(struct op))
#undef MAXABBR

enum optypes getop(char *, int *);

#endif
