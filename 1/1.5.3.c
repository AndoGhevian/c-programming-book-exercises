#include <stdio.h>
#include <locale.h>

#define LOWER 0
#define UPPER 300
#define STEP 20
#define WHILE_CONDITION fahr >= LOWER

/*Print Fahrenheit-Celsius table */
main()
{
/*   int c;

  while((c = getchar()) != EOF)
    putchar(c); */

  /* printf("%d", EOF); */

/*   long nc;

  nc = 0;

  while(getchar() != EOF) {
    ++nc;
    printf("%ld\n", nc);
  } */

 /* double nc;
 for(nc = 0; getchar() != EOF; ++nc);
  printf("%.0f\n", nc); */

  /* int c, nl;

  nl = 0;

  while((c = getchar()) != EOF)
    if(c == '\n')
      ++nl;
  printf("%d\n", nl); */

  /* setlocale(LC_CTYPE, "en_IL");
  printf("%d", 'A'); */

  /* int c;
  long nb, nt, nl;

  nb = 0;
  nt = 0;
  nl = 0;

  while((c = getchar()) != EOF) {
    if(c == ' ')
      ++nb;
    if(c == '\t')
      ++nt;
    if(c == '\n')
      ++nl;
  }

  printf("blanks: %ld, tabs: %ld, newlines: %ld", nb, nt, nl); */

  /* int c;
  long nb;

  for(nb = 0; (c = getchar()) != EOF;) {
    if(c == ' ')
      ++nb;
    if(c != ' ') {
      if(nb != 0) {
        putchar(' ');
        nb = 0;
      }
      putchar(c);
    }
  } */

 /* int c;

 while((c = getchar()) != EOF) {
  if(c == '\t')
    printf("\\t");
  if(c == '\b')
    printf("\\b");
  if(c == '\\')
    printf("\\\\");
  
  if(c != '\t')
    if(c != '\b')
      if(c != '\\')
        putchar(c);
 } */

  
}
