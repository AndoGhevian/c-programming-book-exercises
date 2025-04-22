#include <stdio.h>

struct wnode;

char *noise[] = {
  "and",
  "then"
};

#define NNOISE sizeof noise / sizeof(char *)

long int getword(char *, int);
int binsrch_str(char *, char **, int);
struct wnode *addword(struct wnode *, char *, long int);

void wordprint(struct wnode *);

#define MAXWORD 1000

main() {
  long int ln;
  char word[MAXWORD];
  struct wnode *root = NULL;

  while((ln = getword(word, MAXWORD)) != EOF)
    if(binsrch_str(word, noise, NNOISE) == -1)
      root = addword(root, word, ln);
      /* printf("word %s %ld\n", word, ln); */

  printf("\nwords line numbers list:\n\n");
  wordprint(root);

  return 0;
}

#include <string.h>

int binsrch_str(char *s, char **sptr, int lim) {
  int comp;
  int low, high, mid;

  low = 0;
  high = lim - 1;

  while(low <= high) {
    mid = (low + high) / 2;
    if((comp = strcmp(s, sptr[mid])) < 0)
      high = mid - 1;
    else if(comp > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

#include <ctype.h>
#include "../utils/char_utils.h"

long int getword(char *word, int lim) {
  int c;

  static long int ln = 1;

  while((c = getch()) != EOF && !isalnum(c))
    if(c == '\n')
      ln++;
  if(c == EOF)
    return EOF;

  /* instead of this if check we can
      simply unget c and write a known while loop
   */
  if(--lim);
    for(*word++ = c; --lim && isalnum(c = getch()); *word++ = c);
  /* ungetch(c); */

  if(lim)
    ungetch(c);
  *word = '\0';
  return ln;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct wlnode;

struct wnode {
  char *word;
  struct wlnode *wlines;
  struct wnode *left;
  struct wnode *right;
};

struct wlnode *addline(struct wlnode *, long int);

struct wnode *addword(struct wnode *root, char *word, long int nline) {
  int comp;
  
  if(!root) {
    root = (struct wnode *)malloc(sizeof(struct wnode));
    root->word = malloc(strlen(word) + 1);
    strcpy(root->word, word);
    root->left = root->right = NULL;
    root->wlines = addline(root->wlines, nline);
    return root;
  }

  if((comp = strcmp(word, root->word)) < 0)
    root->left = addword(root->left, word, nline);
  else if(comp > 0)
    root->right = addword(root->right, word, nline);
  else
    root->wlines = addline(root->wlines, nline);

  return root;
}

#include <stdlib.h>

struct wlnode {
  long int ln;
  struct wlnode *left;
  struct wlnode *right;
};

struct wlnode *addline(struct wlnode *root, long int nline) {
  if(!root) {
    root = (struct wlnode *)malloc(sizeof(struct wlnode));
    root->ln = nline;
    root->left = root->right = NULL;
    return root;
  }

  if(nline < root->ln)
    root->left = addline(root->left, nline);
  else if(nline > root->ln)
    root->right = addline(root->right, nline);

  return root;
}

#include <stdio.h>

struct wnode;
void wlinesprint(struct wlnode *tree);

void wordprint(struct wnode *tree) {
  if(!tree)
    return;

  wordprint(tree->left);

  printf("%s  ", tree->word);
  wlinesprint(tree->wlines);
  printf("\n");

  wordprint(tree->right);
}

#include <stdio.h>

struct wlnode;

void wlinesprint(struct wlnode *tree) {
  if(!tree)
    return;

  wlinesprint(tree->left);

  printf("%ld", tree->ln);
  if(tree->right)
    printf(", ");

  wlinesprint(tree->right);
}
