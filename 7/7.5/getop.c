#include <string.h>
#include <ctype.h>
#include "getop.h"

#define MAXABBR 10

static struct op {
  enum optypes type;
  char *abbr[MAXABBR];
  int abbrlen[MAXABBR];
} opabbrs[] = {
  /* ops without abbreviations can be omited */
  { NUMPUSH, {NULL} },
  { VAROP, {NULL} },

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

/* in case if this is required outisde of getop file scope,
it will be required to be defined as a file-scope variable,
not symbolic name because it needs to be resolved at compile-time,
no preprocessing time because structure op tag name is not exposed
to the final users.

numbers format: (+-)(.)ddd, where (opt) is optional part.
*/
#define N_OPABBRS (sizeof opabbrs / sizeof(struct op))

enum optypes getop(char *s, int *oplen) {
  int i;
  char **abbrptr;
  int *abbrlenptr;

  char *snum = s;

  *oplen = 0;
  if(*snum == '+' || *snum == '-')
    snum++;
  if(*snum == '.')
    snum++;
  if(isdigit(*snum))
    return NUMPUSH;

  if(*s == '&')
    return VAROP;

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
