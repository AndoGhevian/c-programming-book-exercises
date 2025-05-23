#include <stdio.h>
#include <string.h>
#include <ctype.h>

int (*transform)(int);

main(int argc, char *argv[]) {
  int c;
  char *nameptr = NULL;

  if(nameptr = strrchr(*argv, '/'))
    nameptr++;
  else
    nameptr = *argv;

  if(strcmp(nameptr, "lower") == 0)
    transform = &tolower;
  else if(strcmp(nameptr, "upper") == 0)
    transform = &toupper;
  else
    transform = NULL;

  if(transform == NULL) {
    printf("invalid call name, allowed: lower, upper\n");
    return 1;
  }

  while((c = getchar()) != EOF)
    putchar((*transform)(c));

  return 0;
}
