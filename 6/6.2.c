/*
  Essentially when grouping things, we need to know the
  exact criteria by which we are grouping.
  so in general we will have things grouped inside
  structures like this: (
      criteria x;
      arrayofthings[];
      group-inside: (
          criteria: y;
          arrayofthings[];
          ...
        )
    )

  best implementation considerations:
  there are 2 different designs for implementation:
  1. using the fact that if we simply sort 
    input words alphabeticaly we will already get all the words
    grouped by any part, like "part1""part2""part3""...rest":
      1. all words with "part1" are adjacent
      2. all words with "part1""part2" are adjacent
      etc.
    here we will need just to sort such that any words with
    width less than given minimum of 6 are put at the
    left of the sorted list.

  2. solve the problem naturaly, applying grouping by provided
  subword.

  when uniquely printing grouped words, both designs
  will be more optimal using binary tree.
  1. array additionaly need on each print do a single comparison
    to previous word to check that words are not equal.
  2. for binary tree we will already omit existing words.
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "../utils/char_utils.h"

/* natural solution */
struct wordgroup {
  char *name;
  struct wordgroup *subgroup;
  struct wordgroup *left;
  struct wordgroup *right;
};

struct wordgroup *addword(struct wordgroup *, char *, int);
void groupedprint(struct wordgroup *, char *, int , int);
int getword(char *, int);

#define MAXWORD 1000

main(int argc, char *argv[]) {
  int gw;
  char word[MAXWORD + 1];
  struct wordgroup *root = NULL;

  gw = argc > 1 ? atoi(argv[1]) : 0;

  if(gw > MAXWORD - 1) {
    printf("variable name maximum width is %d (0 means full word)\n", MAXWORD - 1);
    return -1;
  }

  while(getword(word, MAXWORD) != EOF)
    if(isalpha(word[0]))
      root = addword(root, word, gw);

  printf("Printing:\n");
  groupedprint(root, "", 0, gw);
  return 0;
}

struct wordgroup *addword(struct wordgroup *root, char *word, int maxwidth) {
  int comp, width, wrdw, issmall;

  if(!*word)
    return root;

  wrdw = strlen(word);
  issmall = maxwidth && wrdw < maxwidth;
  width = maxwidth ? maxwidth : wrdw;
  if(!root) {
    root = malloc(sizeof(struct wordgroup));
    root->left = root->right = NULL;
    root->name = malloc(width + 1);
    strncpy(root->name, word, width);
    root->name[width] = '\0';

    root->subgroup = addword(root->subgroup, word + width, 0);
    return root;
  }

  if(issmall)
    /* collect all small words on the left side */
    root->left = addword(root->left, word, maxwidth);
  else if((comp = strncmp(word, root->name, width)) < 0)
    root->left = addword(root->left, word, maxwidth);
  else if(comp > 0)
    root->right = addword(root->right, word, maxwidth);
  else
    root->subgroup = addword(root->subgroup, word + width, 0);

  return root;
}

void groupedprint(struct wordgroup *group, char *prefix, int tabn, int minwidth) {
  int i;
  char *append_pfx = NULL;

  if(!group)
    return;
  if(minwidth && strlen(group->name) < minwidth)
    return;

  groupedprint(group->left, prefix, tabn, minwidth);

  for(i = 0; i < tabn; i++)
    putchar('\t');
  printf("%s%s\n", prefix, group->name);

  append_pfx = malloc(strlen(prefix) + strlen(group->name) + 1);
  *append_pfx = '\0';
  strcat(append_pfx, prefix);
  strcat(append_pfx, group->name);

  groupedprint(group->subgroup, append_pfx, tabn + 1, 0);
  free(append_pfx);

  groupedprint(group->right, prefix, tabn, minwidth);
}

/*
  design considerations.
  we have 2 good solutions:
  1. if we strictly no interested in some types of
    words, we can simply bypass them.
  2. return "/" and "\"" characters appropriately
    for precise task requirements.

  i decide to bypass comments and strings.
*/
int getword(char *word, int lim) {
  int c, endc, c2;

  if(lim < 2) {
    /* no sense to continue reading characters */
    printf("limit of the word must be at least 2 characters");
    return EOF;
  }

  while(isspace(c = getch()));

  endc = c;
  while(c == '/' || c == '\"') {
    if(c == '/') {
      if((c = getch()) != '*') {
        ungetch(c);
        endc = '/';
        break;
      }

      c = getch();
      do {
        c2 = c;
        c = getch();
        if(c2 == EOF || c == EOF)
          break;
      } while(c2 != '*' || c != '/');
    } else if(c == '\"')
      if((c = getch()) != '\"')
        do {
          c2 = c;
          c = getch();
          if(c2 == EOF || c == EOF)
            break;
        } while(c2 == '\\' || c != '\"');

    while(isspace(c = getch()));
    endc = c;
  }

  if(endc == EOF)
    return EOF;

  *word++ = endc;
  if(isalpha(endc)) {
    while(--lim && isalnum(*word++ = getch()));
    if(lim)
      ungetch(*--word);
  }
  *word = '\0';
  return endc;
}
