/* invalid name in book: exercise 5-5 instead of 7-5 (7.5) */

/*design considerations version 1.0.0:
even though problem is related only to
scanf, but because previous chapter was related
to variadic arguments, and previously we also
implemented saving results to variables for postfix
calculator, it is reasonable to implement this task
using more intuitive way, where it is possible to
save results to variadic arguments.

there are 2 possible inputs for calculator,
1. standard input, 2. string literal input, in case
of standard input (1) it will be dangerous from memory management
perspective to support variadic arguments without explicitly providing the
number of variadic arguments. In case of a string literal (2)
its used arguments count known in advance, during coding.
for not string literals reasons/solution are the same
as for standard input (1)

for standard input we can allocate appropriate variables when they
exceeded maximum arguments count limit and then expose those to the caller
as a linked-list or even represent them as a contiguous memory range.

calculator format:
supported operators:
+, -, *, /, % : arithmetic operations
=&n : where n >= 1 indicating appropriate variadic argument
&n : to use its value
print&n : to print n'th argument value for debugging,
  in case if sequential prints are called, they all will
  be printed on the same line other than any input.
clear : clear the calculator stack

extensions:
we also want to support possibility to operate on multiple variadic arguments
at once. for this reasone, it is required for intuitive usage to have
explicitly provide expected arguments count to calculator function,
as for case of dynamic input (standard input).
1. =&n... : pop and assign values starting from variadic argument n till the end.
  stop when variadic argument list end reached or stack is empty.
2. =?n... : same as =&n... but assign 0's to rest of arguments if stack is empty.
3. +&n... : sum and replace each stack value with its appropriate argument starting from n'th.
4. same for * as +&n..., (/, % are not commutative) where - stackval op &n - is performed
5. print&n... : printing arguments (to print something you need to put it in the argument)
6. =..., +..., *..., print... and others for case of &1...

conclusion:
to not complicate the task too much, i will implement
a simplest case with string literal support without
operations on multiple operands.
*/

#include <stdio.h>

main() {

  return 0;
}
