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

struct wordgroup *addword(struct wordgroup *root, char *, int);
void groupedprint(struct wordgroup *root);
int getword(char *, int);

#define MAXWORD 1000

main(int argc, char *argv[]) {
  int gname_w;
  char word[MAXWORD + 1];
  struct wordgroup *root = NULL;

  gname_w = argc > 1 ? atoi(argv[1]) : 0;
  while(getword(word, MAXWORD) != EOF)
    if(isalpha(word[0]))
      root = addword(root, word, gname_w);

  groupedprint(root);
  return 0;
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
      if((c = getch()) != '\"');
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
      ungetch(*word);
  }
  *word = '\0';
  return endc;
}
