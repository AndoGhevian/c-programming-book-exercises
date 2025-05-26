#include <stdio.h>
#include <stdlib.h>

#define min(A, B) ((A) > (B) ? (B) : (A))
#define str_len(A) (sizeof(A) - 1)

#define TABSIZE 4
#define SCREENSIZE 10

/* char representation */
char charrep[10];
char *charrepptr;

int is_printable(int c);

main(int argc, char *argv[]) {
  int c, swi;

  int ts = TABSIZE;
  int sw = SCREENSIZE;
  int parseOct = 1;

  while(*++argv)
    if(strncmp(*argv, "-t", str_len("-t")) == 0)
      ts = (ts = atoi(*argv + str_len("-t"))) > 0 ? ts : TABSIZE;
    else if(strncmp(*argv, "-tab", str_len("-tab")) == 0)
      ts = (ts = atoi(*argv + str_len("-tab"))) > 0 ? ts : TABSIZE;
    else if(strncmp(*argv, "-s", str_len("-s")) == 0)
      sw = (sw = atoi(*argv + str_len("-s"))) > 0 ? sw : SCREENSIZE;
    else if(strncmp(*argv, "-screen", str_len("-screen")) == 0)
      sw = (sw = atoi(*argv + str_len("-screen"))) > 0 ? sw : SCREENSIZE;
    else if(strcmp(*argv, "-h") == 0 || strcmp(*argv, "-hex") == 0)
      parseOct = 0;
    else if(strcmp(*argv, "-o") == 0 || strcmp(*argv, "-oct") == 0)
      parseOct = 1;

  while((c = getchar()) != EOF) {
    if(is_printable(c))
      sprintf(charrep, "%c", c);
    else if(parseOct)
      sprintf(charrep, ";0%.3o;", c);
    else
      /* if byte is more than 8 bit, it is error */
      sprintf(charrep, ";0x%.2x;", c);

    charrepptr = charrep;
    swi = sw;
    if(*charrepptr == '\t') {
      /* printf("aaa t%d w%d", ts, swi); */
      printf("%*s", min(ts, swi), "");
      if((swi -= min(ts, swi)) == 0) {
        putchar('\n');
        swi = sw;
      }
    } else if(*charrepptr == '\n') {
      putchar('\n');
      swi = sw;
    } else {
      int swioffset;
      while(*(charrepptr += (swioffset = printf("%.*s", swi, charrepptr))) != '\0') {
        printf("swi%d %d\n", swi, sw);
        putchar('\n');
        swi = sw;
      }
      swi -= swioffset;
    }
  }

  return 0;
}

#include <ctype.h>

int is_printable(int c) {
  return !ispunct(c);
}
