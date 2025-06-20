#ifndef UTIL_H
#define UTIL_H

#define tostrliteral_helper(V) #V
#define tostrliteral(value) tostrliteral_helper(value)

void *reverse_stack(void *stack, int nextoffsetbytes);

#endif
