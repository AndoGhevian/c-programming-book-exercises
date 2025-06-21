#include <string.h>
#include <ctype.h>
#include "util.h"

#define MAXABBR 10

static struct op {
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

enum optypes getop(char *s, int *oplen) {
  int i;
  char **abbrptr;
  int *abbrlenptr;

  *oplen = 0;
  if(isdigit(*s))
    return NUMPUSH;
  if(*s == '&')
    return VAR;

  for(i = 0; i < N_OPABBRS; i++)
    for(abbrptr = opabbrs[i].abbr, abbrlenptr = opabbrs[i].abbrlen;
      *abbrptr != NULL;
      abbrptr++, abbrlenptr++
    )
      if(strncmp(s, *abbrptr, *abbrlenptr) == 0) {
        *oplen = *abbrlenptr;
        return opabbrs[i].type;
      }
  return UNKNOWN_OP;
}
