/*code design considerations:
implementation which depends on third-party code
glossary:
subset of interface,
extension of interface,
normalization of interface,
out-of-scope behaviour
main:
lets consider simply a private_printf format string handler
implementation ways, which will handle the format appropriate
to standard printf but with some differences.

extensions of a format string handling could be introduced,
in this case we could for example handle whitespaces inside
conversion specifications,
and/or we can have only a subset of format supported by printf,
like omit implementation of some conversion types,
in this case we need to have implementation-defined behaviour for
cutted behaviours or simply define it as out-of-scope behaviour.
for extension of whitespace support inside conversion specification
we have 2 main path:
  - normalize format to be intuitively used with printf supported format
  - define some implementation-defined behaviour
note: case when we can consider whitespaces as out-of-scope behaviour
is not an extension of a format.

for handling out-of-scope behaviours for our function private_printf,
we have 2 ways:
  - we can define it as undefined and pass that cases directly
  to standard printf
  - we can define implementation-defined behaviour for that cases.
  in this case we must not depend on printf behaviour, because third-party
  can change.

this all need to be taken in to account when working on implementation
of a private scanf.
*/

#include <stdio.h>

/*we assume we cant use conversion type 'n' because
  in this chapter we have not introduced it.

  for not supported conversion specifications
  (out-of-scope format specifications) we will
  assume no-match behaviour.

  considerations:
  firstly we thought to consider not supported specfications
  as simple character sequances to match. but in this case
  it occures that we are supporting invalid formats
  instead of mitigating them.
  In case when we consider them as invalid, we simply need
  to stop parsing, because there is no simple implementation
  to handle them as character sequance, and for simple implementations
  limitations can occure.

  implementation algorithm description:
  1. we read until conversion specification (valid/invalid),
  2. check if specification is invalid, then apply scanf
    to format string already read.
  3. if specification is valid, then apply scanf against appropriate
    type pointer argument, and in case if it return 1,
    increment matched and assigned converted values and
    continue from step 2, otherwise if return 0,
    return converted values counter.

  notes:
    valid or invalid refere to supported by our private
    scanf format conversion specifications (even custom),
    not original scanf.
 */

main() {

  return 0;
}
