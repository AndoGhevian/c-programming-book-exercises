#include <stdio.h>
#include <stdlib.h>

enum streamerrs {
  SRCBROKEN = 1,
  DISTBROKEN
};

enum streamerrs filecopy(FILE *ifp, FILE *ofp);

main(int argc, char *argv[]) {
  enum streamerrs err_t;
  FILE *fp;

  char *prog = argc >= 1 ? *argv : "unnamed";

  if(argc == 0 || argc == 1) {
    if((err_t = filecopy(stdin, stdout)) != 0)
      switch(err_t) {
        case SRCBROKEN:
          fprintf(stderr, "%s command: unable to read from standard input.\n", prog);
          break;
        case DISTBROKEN:
          fprintf(stderr, "%s command: unable to write to standard output.\n", prog);
          exit(2);
          break;
        default:
          break;
      }
  } else
    while(--argc > 0)
      if((fp = fopen(*++argv, "r")) != NULL) {
        if((err_t = filecopy(fp, stdout)) != 0)
          switch(err_t) {
            case SRCBROKEN:
              fprintf(stderr, "%s command: unable to continue read file %s while copying.\n", prog, *argv);
              break;
            case DISTBROKEN:
              fprintf(stderr, "%s command: unable to write to standard output while copying file %s.\n", prog, *argv);
              exit(2);
              break;
            default:
              break;
          }
        fclose(fp);
      }
      else
        fprintf(stderr, "%s command: unable to open a file %s to copy.\n", prog, *argv);

  return 0;
}

enum streamerrs filecopy(FILE *ifp, FILE *ofp) {
  int c;

  while((c = getc(ifp)) != EOF && putc(c, ofp) != EOF);
  if(ferror(ifp))
    return SRCBROKEN;
  if(ferror(ofp))
    return DISTBROKEN;
  return 0;
}
