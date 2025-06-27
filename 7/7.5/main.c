/* invalid name in book: exercise 5-5 instead of 7-5 (7.5) */

/*design considerations version 2.0.0:
even though problem is related only to
scanf, but because previous chapter was related
to variadic arguments, and previously we also
implemented saving results to variables for postfix
calculator, it is reasonable to implement this task
using more intuitive way, where it is possible after
calulations to expose variables as variadic arguments.

for this reasone we will use a "variable exposure configuration"
string of format: "&5   &1     &7...&10" arguments will match to contiguouse
sequance of variadic arguments: &5->va1, &1->va2, &7->va3, &8->va4, &9->va5, &10->va6.
Because of this configuration string developer will already know how many variadic
arguments to provide. each configuration entity corresponds to next variadic argument in the list.
note: opposite to processing of "calculations input format"
  for multy variable operations, where input variables are proccessed from the last one,
  for "exposure configuration" variadic arguments stack is upside down,
  and the end of a stack, from where arguments are retrived is the start of
  variadic arguments list.

during calculations float objects will be allocated for explicitely assigned variables
1. it could be returned as a pointers array float *vars[] (finishing with NULL pointer)
to caller, or 2. after assigning values to variadic arguments these memory need to be freed.

calculator format:
+, -, *, /, % : arithmetic operations
=&n : where n >= 1 indicating appropriate variable
&n : to put its value on the stack
print&n : to print n'th vairable value for debugging,
  in case if sequential prints are called, they all will
  be printed on the same line other than any input.
clear : clear the calculator stack

not assigned variable value default's to 0.

note: we use scanf, which is to indicate whether
some calculation operation in the input are of valid
format it is required to put at leats one
parsable data type at the end of the scanf format.

extensions:
we also want to support possibility to operate on multiple variables
at once.
previous design assumes that provided the first variable,
the operation is performed on it and each subsequant variable,
but in this case, if &6 for example not encountered during calculations
and we are executing =&1... it doesnt know that there is &6 exists,
so operation is not intuitive and hard to track the results.

in the new version of multy-operations format is =...&6 with optional start
variable =&3...&6, in this case if there is appropriate value in the stack
variable will be created and operation will be performed as intended, unitl
stack end or vairiables list exhausted.
1. =...&n (=&m...&n) : pop and assign values from calculator stack until its empty
  or end of assign variables reached. in case if start vairable index is greater
  than end variable index, assignement will be performed in reversed order.

  =&1...&3 (same as =...&3) result to: &3 = pop(), &2 = pop(), &1 = pop()
  =&3...&1 result to: &1 = pop(), &2 = pop(), &1 = pop()
  cycle finish if end of stack is reached.

3. implement "prefix" arithmetic operators:
  +...&n (same as +&1...&n) or even reversed version with +&n...&1

  interpreted as valn = pop() + &n, valn-1 = pop() + &n-1, val1 = pop() + &1 and then push all these
  to the stack again, push(val1), ...push(valn) (same for reversed)
4. implement "postfix" arithmetic operators :
  in which case operator puted at the end ...&n/ (same as &1...&n/) or reversed one
  &n...&1/
5. print...&n (same as print&1...&n) : printing variable values
  from n to 1, if variable didn't allocated it prints 0.
  to print something you need to put it in the variable.
6. print... to print all existing variables,
  with their appropriate numbers, omit not allocated ones.
7. ..&n or &4...&n will push multiple values to calculator stack

multy operations between stack values are not defined
e.g sum of all values in the stack.

conclusion:
most importanty, new syntax for extensions is easy to implement
using simple sscanf. second is that we will not expose internaly
allocated memory to caller, but simply will free it on function return.
also the variable exposure configuration format will support
the same syntax for multiple variable operations.

input exact format breakdown:
all entities required to be separated by spaces,
not separated by spaces operands and operators considered
as invalid and will not have effect.
*/

#include <stdio.h>

main() {


  return 0;
}

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include "calcerr.h"
#include "printvars.h"
#include "vartable.h"
#include "var.h"
#include "varexpose.h"
#include "getop.h"
#include "util/util.h"

#define MAXOP 100
static char calcop[MAXOP];
static char oprest[MAXOP];

#define MAXCALCSTACK 1000
static float numstack[MAXCALCSTACK];
static float *stackptr = numstack;
static float *stackend = numstack + MAXCALCSTACK;

int postfixcalc(char const *input, char const *exposefmt, ...) {
  va_list ap;

  int c, i, iter;
  float *stackvalptr, op1, op2;

  struct varexpose *exposelist, *exposenode;

  int operr, printseq;
  enum optypes opt;

  int var_start, var_end;
  int var_offset, postfixop_offset, postfixop;
  enum var_entities tvar;

  float fnum;
  int printop_spread;

  exposelist = parse_varexposeconfig(exposefmt);
  if(exposelist == NULL) {
    /* future: handle error of parsing through varexp_errno
    and varexp_errstr */
    printf("invalid expose configuration entity encountered.");
    return 1;
  }

  c = getch(input); /* or c = ' ' */
  do {
    printseq = 0;
    for(; isspace(c); c = getch(input))
      if(c == '\n')
        printseq = 1;

    if(printseq) {
      flushprintvars();
      flusherrors();
    }
    printseq = 0;

    for(i = 0; c != EOF && !isspace(c) && i < MAXOP - 1; c = getch(input), i++)
      calcop[i] = c;
    calcop[i] = '\0';

    if(c == EOF || c == '\n')
      printseq = 1;

    operr = 0;
    printop_spread = 0;
    var_offset = postfixop_offset = postfixop = 0;
    switch((opt = getop(calcop, &var_offset))) {
      case NUMPUSH:
        if(operr = sscanf(calcop, "%f%s", &fnum, oprest) == 2)
          push_calcerr(INVALID_FLOAT);
        break;
      case VAROP:
        tvar = parse_varstr(calcop, &var_start, &var_end, oprest);
        if(operr = tvar == INVALID_VAR_STR)
          push_calcerr(INVALID_VAR);
        else
          switch(getop(oprest, &postfixop_offset)) {
            case ADD:
              opt = ADDVAR;
            case MUL:
              opt = MULVAR;
            case SUBTR:
              opt = SUBTRVAR;
            case DIV:
              opt = DIVVAR;
              postfixop = 1;
              if(*(oprest + postfixop_offset) != '\0') {
                push_calcerr(INVALID_VAR_POSTFIX_OP);
                operr = 1;
              }
              break;
            default:
              push_calcerr(UNKNOWN_VAR_POSTFIX_OP);
              operr = 1;
              break;
          }

        /* check only if valid var operation */
        if(!operr)
          if(tvar == VAR_RANGE && var_end <= 0 || var_start <= 0) {
            push_calcerr(INVALID_NOT_POSITIVE_VAR);
            operr = 1;
          }
        break;
      case ADD:
      case MUL:
      case SUBTR:
      case DIV:
        if(*(calcop + var_offset) != '\0') {
          push_calcerr(INVALID_CALC_OP);
          operr = 1;
        }
        break;
      case PRINTVAR:
        if(strcmp(calcop + var_offset, "...") == 0) {
          printop_spread = 1;
          break;
        }
      case VARASSIGN:
      case ADDVAR:
      case MULVAR:
      case SUBTRVAR:
      case DIVVAR:
        tvar = parse_varstr(calcop + var_offset, &var_start, &var_end, oprest);
        if(tvar == INVALID_VAR_STR) {
          if(opt == PRINTVAR)
            push_calcerr(INVALID_VAR_IN_PRINT_OP);
          else
            push_calcerr(INVALID_VAR_IN_PREFIX_OP);
          operr = 1;
        } else  if(*oprest != '\0') {
          push_calcerr(INVALID_OP_EXTRA_PART);
          operr = 1;
        } else if(tvar == VAR_RANGE && var_end <= 0 || var_start <= 0) {
          push_calcerr(INVALID_NOT_POSITIVE_VAR);
          operr = 1;
        }
        break;
      case UNKNOWN_OP:
        push_calcerr(UNKNOWN_CALC_OP);
        operr = 1;
        break;
      case CLEARSTACK:
        break;
      default:
        push_calcerr(NOT_IMPLEMENTED_CALC_OP);
        operr = 1;
        break;
    }

    if(printseq) {
      flushprintvars();
      flusherrors();
    }
    printseq = 0;

    if(operr)
      continue;

    /*here calc operation is already proven to be valid */
    switch(opt) {
      case NUMPUSH:
        *stackptr++ = fnum;
        break;
      case VAROP:
        /* opposite to operations against vars, var push work
          as a list against suggestedvars, not as a stack. */
        if(tvar == SINGLE_VAR && stackptr != stackend)
          *stackptr++ = lookupvar(var_start);
        else if(tvar == VAR_RANGE)
          for(i = var_start, iter = 1;
            iter && stackptr != stackend;
            iter = iterateint(&i, var_end)
          )
            *stackptr++ = lookupvar(i);
        /*future: show calc stack full error*/
        break;
      case ADDVAR:
      case MULVAR:
      case SUBTRVAR:
      case DIVVAR:
      case VARASSIGN:
          if(stackptr == numstack)
            break;
          if(tvar != SINGLE_VAR || tvar != VAR_RANGE)
            /* not implemented var type */
            break;

          stackvalptr = stackptr - 1;
          for(i = tvar == VAR_RANGE ? var_end : var_start, iter = 1;
            iter;
            stackvalptr--, iter = tvar == VAR_RANGE && iterateint(&i, var_start)
          ) {
            switch(opt) {
              case ADDVAR:
                *stackvalptr += lookupvar(i);
                break;
              case MULVAR:
                *stackvalptr *= lookupvar(i);
                break;
              case SUBTRVAR:
                if(postfixop)
                  *stackvalptr = lookupvar(i) - *stackvalptr;
                else
                  *stackvalptr -= lookupvar(i);
                break;
              case DIVVAR:
                if(postfixop)
                  *stackvalptr = lookupvar(i) / *stackvalptr;
                else
                  *stackvalptr /= lookupvar(i);
                break;
              case VARASSIGN:
                installvar(i, *stackvalptr);
                stackvalptr--;
                /* future: handle not enough memory for var install error */
                break;
              default:
                break;
            }
            if(stackvalptr == numstack)
              break;
          }
          break;
      case ADD:
      case MUL:
      case SUBTR:
      case DIV:
        op1 = op2 = 0;
        if(stackptr == numstack)
          break;
        else if(stackptr == numstack + 1)
          op2 = *--stackptr;
        else {
          op2 = *--stackptr;
          op1 = *--stackptr;
        }

        switch(opt) {
          case ADD:
            *stackptr++ = op1 + op2;
            break;
          case MUL:
            *stackptr++ = op1 * op2;
            break;
          case SUBTR:
            *stackptr++ = op1 - op2;
            break;
          case DIV:
            *stackptr++ = op1 / op2;
            break;
          default:
            break;
        }
        break;
      case CLEARSTACK:
        stackptr = numstack;
        break;
      case PRINTVAR:
        if(printop_spread)
          push_printvarspread();
        else if(tvar == SINGLE_VAR)
          push_printvar(var_start);
        else if(tvar == VAR_RANGE)
          push_printvarrange(var_start, var_end);
        break;
      default:
        break;
    }
  } while(c != EOF);

  va_start(ap, exposefmt);
  for(exposenode = exposelist; exposenode != NULL; exposenode = exposenode->next)
    switch(exposenode->type) {
      case EXPOSE_FLOAT:
        *va_arg(ap, float *) = lookupvar(exposenode->i);
        break;
      default:
        printf("not supported expose type.\n");
        break;
    }
  va_end(ap);

  /*here we need to free memory for exposelist and variables*/
  if(exposelist)
    free_linked_list(exposelist, (char *)&exposelist->next - (char *)exposelist);
  free_vartable();
}
