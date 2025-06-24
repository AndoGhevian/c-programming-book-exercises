#ifndef UTIL_H
#define UTIL_H

#define tostrliteral_helper(V) #V
#define tostrliteral(value) tostrliteral_helper(value)

void *reverse_stack(void *, int );
void free_linked_list(void *, int);

/* here we define a global variable
instead of symbolic name to not allocate
each time an empty string (1 character array '\0').
*/
char const *RESET_GETCH = "";

/* NULL to read from standard input.
before changing source you need to reset getch.
to reset reading you need to pass RESET.
RESET simply an empty string defined in
util header. otherwise after EOF all
subseqent calls will return EOF unitl reset.
*/
int getch(char *);

#endif
