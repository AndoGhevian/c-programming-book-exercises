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
arguments to provide.

during calculations float variables will be allocated for &1, &2 etc.
1. it could be returned as a pointers float * array (finishing with NULL pointer)
to caller, or 2. after assigning values to variadic arguments these memory can be freed.

calculator format:
supported operators:
+, -, *, /, % : arithmetic operations
=&n : where n >= 1 indicating appropriate variable
&n : to use its value
print&n : to print n'th vairable value for debugging,
  in case if sequential prints are called, they all will
  be printed on the same line other than any input.
clear : clear the calculator stack

extensions:
we also want to support possibility to operate on multiple variables
at once.
previous design assumes that provided the first variable,
the operation is performed on it and each subsequant variable,
but in this case, if &6 for example not encountered during calculations
and we are executing =&1... it doesnt know that there is &6 exists,
so operation is not intuitive and hard to track the results.

in the new version of multy-operations format is =...&6 with optional start
variable =&3...&6, in this case if encountered yet, all variables until &6
will be created and operation will be performed as intended.
1. =...&n (=&m...&n) : pop and assign values from calculator stack until its empty
  or end of assign variables reached. in case if start vairable index is greater
  than end variable index, assignement will be performed in reversed order.

  =&1...&3 (same as =...&3) result to: &3 = pop(), &2 = pop(), &1 = pop()
  =&3...&1 result to: &1 = pop(), &2 = pop(), &1 = pop()
  cycle finish if end of stack is reached.

2. (optional implementation) =?...&n (same as =?1...&n) : same as =...&n
  but assign 0's to rest of arguments if stack is empty.
3. (optional implementation) implement for arithmetic operators "prefix":
  +...&n (same as +&1...&n) or even reversed version with +&n...&1

  interpreted as val1 = pop() + &n, val2 = pop() + &n - 1, valn = pop() + &1 and then push all these
  to the stack again, push(valn), ...push(val1) (same for reversed)
4. (optional implementation) implement for arithmetic operators "postfix":
  in which case operator puted at the end ...&n/ (same as &1...&n/) or reversed one
  &n...&1/
5. print...&n (same as print&1...&n) : printing arguments (to print something you need to put it in the variable)
6. print... to print all existing variables.
*/

#include <stdio.h>

main() {

  return 0;
}
