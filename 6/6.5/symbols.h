#ifndef SYMBOLS_H
#define SYMBOLS_H

struct nlist {
  struct nlist *next;
  char *name;
  char *defn;
};

struct nlist *lookup(char *);
struct nlist *install(char *, char *);
/* returns defn to not perform lookup twice */
char *uninstall(char *);

#endif
