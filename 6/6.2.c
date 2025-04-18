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
#include <string.h>

main() {
  return 0;
}
