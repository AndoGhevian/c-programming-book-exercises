#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols.h"

static int hash(char *, int);
static char *l_strdup(char *);

#define TABSIZE 101
static struct nlist *hashtab[TABSIZE];

struct nlist *install(char *symbol, char *text) {
  int hashval;
  struct nlist *symblock;

  if((symblock = lookup(symbol)) == NULL) {
    symblock = (struct nlist *)malloc(sizeof( struct nlist));
    if(symblock == NULL || (symblock->name = l_strdup(symbol)) == NULL) {
      free((void *)symblock); /* to prevent memory leaks */
      return NULL;
    }

    symblock->next = hashtab[hashval = hash(symbol, TABSIZE)];
    hashtab[hashval] = symblock;
  } else
    free((void *)symblock->defn);

  if((symblock->defn = l_strdup(text)) == NULL)
    return NULL;
  return symblock;
}

struct nlist *lookup(char *name) {
  struct nlist *np;
  for(np = hashtab[hash(name, TABSIZE)]; np != NULL; np = np->next)
    if(strcmp(np->name, name) == 0)
      return np;
  return NULL;
}

char *uninstall(char *name) {
  char *defn;
  struct nlist *np;

  if((np = lookup(name)) == NULL)
    return NULL;
  free((void *)np->name);
  defn = np->defn;
  free((void *)np);
  return defn;
}

static char *l_strdup(char *s) {
  char *scp;
  if(scp = (char *)malloc(strlen(s) + 1))
    strcpy(scp, s);
  /* i think exlicit return NULL is more readable */
  return scp;
}

/* lowercase alpha, digits */
#define MAXCHARRANK 36
static int hash(char *s, int distribn) {
  int hashval;

  for(hashval = 0; *s != 0; s++)
    hashval = (*s + MAXCHARRANK * hashval) % distribn;
  return hashval;
}
