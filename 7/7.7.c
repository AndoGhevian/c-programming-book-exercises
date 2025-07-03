/* invalid-implementation:
  because sometimes the line we read with gets breaks a pattern we
  are searching for, e.g we read "123456789hel" then "lo some text",
  each 12 character lines, so even though there is a pattern "hello",
  we can not find it.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum PROG_TERMINATIONS {
  NOT_SUPPORTED_ENVIORNMENT = 1,
  NO_SEARCH_PATTERN_PROVIDED,
  FILENAMES_EMPTY_LIST
};

int local_fgets(char *, int, FILE *);

#define MAXLINE 20
char line[MAXLINE];

/* command format: find pattern1 pattern2 ... -x -n -p -x -f filename1 filename2 ...
to print only found result lines use "cat command" with standard input.
-x - exclude patterns
-n - print line numbers and filenames if they are provided by -f flag
  before each found line
-f - filenames list to search for, consume the rest of arguments list.
-p - specifies pattern, to not inerfere with optional command arguments,
  example is "find -p -x", where -x considered as a pattern.

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

  char ** const arg1 = argv;
  char *prog;
  char **filenames, *currname;
  char **lastpattern, **pattern;
  int except, printline;

  int found, nline, len;

  if(argc = 0) {
    fprintf(stderr, "command unnamed: invalid call of command.\n");
    return NOT_SUPPORTED_ENVIORNMENT;
  }

  except = printline = 0;
  prog = *arg1;

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

  if(lastpattern == arg1) {
    fprintf(stderr, "command %s: should provide at least one search pattern.\n", prog);
    exit(NO_SEARCH_PATTERN_PROVIDED);
  }

  /* current implementation handles file at a time (no concurrency). */
  if(*argv == NULL) {
    currname = NULL;
    filenames = --argv;
  } else if((currname = *++argv) == NULL) {
    fprintf(stderr, "command %s: file names list can not be empty.\n", prog);
    exit(FILENAMES_EMPTY_LIST);
  } else
    filenames = argv;

  do {
    fp = currname != NULL ? fopen(currname, "r") : stdin;
    nline = 1;
    while((len = local_fgets(line, MAXLINE, fp)) > 0) {
      found = 0;
      pattern = arg1 + 1;
      while(pattern <= lastpattern)
        if(found = strstr(line, *pattern++) != NULL != except)
          break;

      if(found) {
        if(printline) {
          if(currname)
            printf("<%s> ", currname);
          printf("%d: ", nline);
        }
        printf("%s", line);
        if(line[len - 1] != '\n')
          putchar('\n');
      }

      if(line[len - 1] == '\n')
        nline++;
    }

    if(len == EOF)
      fprintf(stderr,
        "command %s: error while reading from %s.\n",
        prog,
        currname != NULL ? currname : "standard input");
  } while((currname = *++filenames) != NULL);

  return 0;
}

#include <stdio.h>

int local_fgets(char *s, int n, FILE *fp) {
  register int c, len;
  register char *cs;

  cs = s;
  len = 0;
  while(--n > 0 && (c = getc(fp)) != EOF) {
    *cs++ = c;
    len++;

    if(c == '\n')
      break;
  }

  if(cs != s)
    *cs = '\0';

  if(ferror(fp))
    return EOF;
  return len;
}
