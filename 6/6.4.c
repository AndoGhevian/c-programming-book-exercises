#include <stdio.h>

struct wnode;
struct fnode;

int getword(char *, int);
struct wnode *addword(struct wnode *, char *);
struct fnode *scanwordfreq(struct fnode *, struct wnode *);

void printfreq(struct fnode *);

#define MAXWORD 1000

main() {
  char word[MAXWORD];
  struct wnode *root = NULL;
  struct fnode *freqroot = NULL;

  while(getword(word, MAXWORD) != EOF)
    root = addword(root, word);

  freqroot = scanwordfreq(freqroot, root);

  printf("\nword frequences:\n\n");
  printfreq(freqroot);

  return 0;
}

#include <stdio.h>
#include <ctype.h>
#include "../utils/char_utils.h"

int getword(char *word, int lim) {
  int c;

  while((c = getch()) != EOF && !isalnum(c));
  if(c == EOF)
    return EOF;

  if(--lim)
    for(*word++ = c; --lim && isalnum(c = getch()); *word++ = c);

  if(lim)
    ungetch(c);
  *word = '\0';

  return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct wnode {
  char *word;
  int count;
  struct wnode *left;
  struct wnode *right;
};

struct wnode *addword(struct wnode *root, char *word) {
  int comp;

  if(!root) {
    root = (struct wnode *)malloc(sizeof(struct wnode));
    root->word = malloc(strlen(word) + 1);
    strcpy(root->word, word);
    root->count = 1;
    root->left = root->right = NULL;
    return root;
  }

  if((comp = strcmp(word, root->word)) < 0)
    root->left = addword(root->left, word);
  else if(comp > 0)
    root->right = addword(root->right, word);
  else
    root->count++;

  return root;
}

struct fnode;

struct fnode *addfreq(struct fnode *, struct wnode);
struct fnode *scanwordfreq(struct fnode *ftree, struct wnode *wtree) {
  if(!wtree)
    return ftree;

  ftree = addfreq(ftree, *wtree);
  scanwordfreq(ftree, wtree->left);
  scanwordfreq(ftree, wtree->right);
  return ftree;
}

struct fnode {
  int count;
  /* not a structure pointer */
  struct wnode wordtree;
  struct fnode *left;
  struct fnode *right;
};

struct fnode *addfreq(struct fnode *root, struct wnode wordnode) {
  if(!root) {
    root = (struct fnode *)malloc(sizeof(struct fnode));
    root->count = wordnode.count;
    root->left = root->right = NULL;

    wordnode.left = wordnode.right = NULL;
    root->wordtree = wordnode;
    return root;
  }

  if(wordnode.count < root->count)
    root->left = addfreq(root->left, wordnode);
  else if(wordnode.count > root->count)
    root->right = addfreq(root->right, wordnode);
  else
    addword(&root->wordtree, wordnode.word);

  return root;
}

#define MAXWORDPREFIX 100
char wordprefix[MAXWORDPREFIX];

void printword(struct wnode *, char *);
void printfreq(struct fnode *ftree) {
  if(!ftree)
    return;

  printfreq(ftree->right);

  sprintf(wordprefix, "%4d  ", ftree->count);
  /* word tree is always exists if frequency exists. */
  printword(&ftree->wordtree, wordprefix);

  printfreq(ftree->left);
}

void printword(struct wnode *wtree, char *prefix) {
  if(!wtree)
    return;

  printword(wtree->left, prefix);

  printf("%s%s\n", prefix, wtree->word);

  printword(wtree->right, prefix);
}
