/*solution considerations:
  preprocessor's code scanning is
  ended up in a loop with steps (this is casual definition):
  Read input and perform this actions on tokens:
    1. if no directive, search encountered token in symbol table:
      1. if found peform following steps on replacement text:
        1. perform all concatenations of tokens adjacent to ##(token-pasting operator).
        2. replace symbolic names with appropriate replacement texts.
        3. rescan if one of the previous steps occure.
      2. if token was in symbol table replace it by result of a previous step.
      3. if token was not in symbol table add token.
    2. if define directive encountered, register/redefine
      symbolic name, replacement text pair in table.
    3. if undef directive encounter, remove symbolic name from table.

  comments inside the code text must be omitted.
  tokens inside strings, characters are not replaced.
  (including comments and strings inside replacement text)
*/

#include <stdio.h>
struct nlist;

enum {
  STRING = EOF - 1000,
  COMMENT,
  DEFINE,
  NAME,
  NUMBER,
  UNKNOWN
};

int gettoken(void);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);

main() {
  return 0;
}

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};
