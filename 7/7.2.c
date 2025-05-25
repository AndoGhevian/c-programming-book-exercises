#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define TABSIZE 4
#define SCREENWIDTH 50

enum nongraphic_parse_type {
  OCT,
  HEX
};

char octhex[10];
/* alternative solution */
/* char octcode[] = "0ooo";
char hexcode[] = "0xhh"; */

int isprint_local(int);

main(int argc, char *argv[]) {
  int c, ohlen, wi, ti, ohi;
  
  int ptype = OCT;
  int ts = TABSIZE;
  int sw = SCREENWIDTH;

  int valoffset;
  int ntemp;
  while(*++argv)
    if(strncmp(*argv, "-t", valoffset = 2) == 0 || strncmp(*argv, "-tab", valoffset = 4) == 0)
      ts = (ntemp = atoi(*argv + valoffset)) > 0 ? ntemp : ts;
    else if(strncmp(*argv, "-w", valoffset = 2) == 0 || strncmp(*argv, "-width", valoffset = 6) == 0)
      sw = (ntemp = atoi(*argv + valoffset)) > 0 ? ntemp : sw;
    else if(strcmp(*argv, "-h") == 0 || strcmp(*argv, "-hex") == 0)
      ptype = HEX;

  wi = sw;
  while((c = getchar()) != EOF)
    if(isprint_local(c)) {
      putchar(c);
      if(--wi == 0) {
        wi = sw;
        putchar('\n');
      }
    } else if(c == '\n') {
      wi = sw;
      putchar('\n');
    } else if(c == '\t')
      for(ti = ts; ti > 0; ti--) {
        putchar(' ');
        if(--wi == 0) {
          wi = sw;
          putchar('\n');
        }
      }
    else {
      switch(ptype) {
        case OCT:
          ohlen = sprintf(octhex, ";0%.3o", c);
          break;
        case HEX:
          ohlen= sprintf(octhex, ";0x%.2x", c);
          break;
        default:
          break;
      }

      for(ohi = 0; ohi < ohlen; ohi++) {
        putchar(octhex[ohi]);
        if(--wi == 0) {
          wi = sw;
          putchar('\n');
        }
      }
    }
}

int isprint_local(int c) {
  return isprint(c);
  /* to see how characters are converted to oct/hex */
  /* return ispunct(c) ? 0 : isprint(c); */
}
