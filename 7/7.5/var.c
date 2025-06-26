#include <stdio.h>
#include "var.h"

/*there are several possible implementations
that this function could have, we will use the most optimal one,
but first lets discuss some possible solutions:

note: for solution we can not use functions and features that we
have not covered yet in previous chapters. so, no strtol or scanf %n. 

1. we can limit the size of variable string and use that fact to safely
store temporary rest part in private array of that size while scanning
it.

this solution come to mind because the argument "rest" is not safe for
temporary values, if a user knows what size it requires in advance,
he could provide even a single characer array, but given we first
trying to scan the first &ddd part and storing the rest to scan it later,
then it could fall outside the array memory segment.

by the way, this limitation encompasses the var rest part,
which is not natural limitation for input.

well with this limitation, we can provide very simple
solution: scanf &ddd&rest_str, and then apply
scanf ...&ddd&rest_str|var_str, so in simple words,
we get first variable then store later part in a temporary string,
then we scan that string second time (first time we store it) to extract
range end variable and the final rest part.

although this solution is simple, it is very suboptimal. because
we are scaning the whole second possible part
(part of a range and the rest string part) 2 times, even though it could be
very long string.

2. second solution, is the optimal one. we are omiting limitation
of a variable string, then we simply scanning using scanf the input
so that sequance of scans extracting the seqence of rest parts, growing
from small to big size strings, so to store those values in provided
array of rest part is safe as long as a user knows that he provides
enough space for the rest part.
in this case, even though our calls to scanf will read full first
variable and "...&" (4 characters) range indicator part 2 times, but, it will not
pass through to the end of unknown length input string,
and using assumption that &ddd ddd-number part is of reasonable width,
it will require a few character reads to trap errors, and the rest part
will be read, only one time.

future improvement: we can add a s_rest NULL pointer support
to drain the rest part.
*/
enum var_entities parse_varstr(char const *s, int *var_start, int *var_end, char *s_rest) {
  int n;

  /* initializing with 0 to not handle separately
  cases when scanf %s encounter no rest string */
  *s_rest = '\0';
  if((n = sscanf(s, "&%d...&%d%s", var_start, var_end, s_rest)) == 3 || n == 2)
    return VAR_RANGE;
  else if(n == 1) {
    /* it will read second time only part with &%d...& which is, in case
      if variable number is of a reasonable size, will be a few characters,
      tending to constant reads count of 16, or so. */
    sscanf(s, "&%*d%s", s_rest);
    return SINGLE_VAR;
  }
  else if(n == 0)
    if((n = sscanf(s, "...&%d%s", var_end, s_rest)) == 0 || n == EOF)
      return INVALID_VAR_STR;
    else
      return VAR_RANGE;
  else
    return INVALID_VAR_STR;
}
