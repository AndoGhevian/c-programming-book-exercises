#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* command format: find pattern1 pattern2 ... -x -n -p -x -f filename1 filename2 ...
to print only found result lines use "cat command" with standard input.
-x - exclude patterns
-n - print line numbers and filenames if they are provided by -f flag
  before each found line
-f - filenames list to search for, consume the rest of arguments list.
-p - specifies pattern, to not inerfere with optional command arguments
  like find -p -x, where -x considered as a pattern.

at leats one pattern should be provided.

in the future, search could be concurent for different files, so if
printing numbers of lines, it is necessery to print filenames to identify
what file line it is. to handle files sequentially use "cat command"
to combine files.

note: pattern is a positional argument so it should come immediately after
find command, and then only the optionals.
*/
main(int argc, char *argv[]) {
  FILE *fp;

  char *prog;
  char **filenames, *currname;
  char **lastpattern;
  int except, printline;

  if(argc = 0) {
    fprintf(stderr, "command unnamed: invalid call of command.\n");
    return 1;
  }

  except = printline = 0;
  prog = *argv;

  lastpattern = argv;
  while(*++argv && (*argv)[0] != '-')
    lastpattern = argv;

  for(; *argv && strcmp(*argv, "-f") != 0; argv++)
    if(*(*argv)++ != '-')
      fprintf(stderr, "command: %s: argument %s skipped, positional arguments should come before optionals.\n", prog, --*argv);
    else
      switch(**argv) {
        case 'x':
          except = 1;
          break;
        case 'n':
          printline = 1;
          break;
        case 'p':
          *++lastpattern = *++argv;
          break;
        default:
          fprintf(stderr, "command %s: not supported optional argument -%s.\n", prog, *argv);
          break;
      }

  if(lastpattern == prog) {
    fprintf(stderr, "command %s: should provide at least one search pattern.\n", prog);
    exit(2);
  }

  /* current implementation handles file at a time (no concurrency). */
  if(*argv == NULL) {
    currname = NULL;
    filenames = --argv;
  } else if((currname = *++argv) == NULL) {
    fprintf(stderr, "command %s: file names list can not be empty.\n");
    exit(3);
  } else
    filenames = argv;

  do {
    fp = currname != NULL ? fopen(currname, "r") : stdin;
    
    /* here searching pattern for file/stdin */
  } while((currname = *++filenames) != NULL);

  return 0;
}
