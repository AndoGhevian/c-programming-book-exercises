#ifndef UTIL_H
#define UTIL_H

#define tostrliteral_helper(V) #V
#define tostrliteral(value) tostrliteral_helper(value)

#define fillzero(arr, count) do {int i; for(i = 0; i < (count); i++) arr[i] = 0;} while(0)

void *reverse_stack(void *stack, int nextoffsetbytes);

#endif
