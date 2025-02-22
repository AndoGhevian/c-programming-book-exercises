#include <stdio.h>

// int power(int, int);
float fahrenheit_to_celsius(int);

main() {
  int i, lower, upper, step;
  
  lower = 0;
  upper = 300;
  step = 20;

  printf("Fahrenheit\tCelsius\n");
  for(i = lower; i <= upper; i = i + 20)
    printf("%10d\t%7.2f\n", i, fahrenheit_to_celsius(i));
}

float fahrenheit_to_celsius(int fahr) {
  return (5.0 / 9.0) * (fahr - 32);
}

int power(int base, int n) {
  int p, i;

  p = 1;
  for(i = 1; i <= n; ++i) {
    p = p * base;
  }

  return p;
}



/* #include <stdio.h>

#define CHARS_COUNT 5

main() {
  int c, i;
  int chars[CHARS_COUNT];
  int char_freq[CHARS_COUNT];

  for(i = 0; i < CHARS_COUNT; ++i) {
    chars[i] = -1;
    if(i == 0)
      chars[i] = 'b';
    if(i == 3)
      chars[i] = 'a';
  }

  for(i = 0; i < CHARS_COUNT; ++i)
    char_freq[i] = 0;

  while((c = getchar()) != EOF) {
    for(i = 0; i < CHARS_COUNT; ++i) {
      if(c == chars[i])
        ++char_freq[i];
    }
  }

  printf("Character\tFrequency\n");
  for(i = 0; i < CHARS_COUNT; ++i)
    if(chars[i] != -1) {
      printf("%9c:\t%9d\n", chars[i], char_freq[i]);
    }
}
 */


/*  
  #define MAX_WORD_LENGTH 4
  #define IN 1
  #define OUT 0

  int c, i, nlong_words, wl, state;

  int nword_length[MAX_WORD_LENGTH];
  for(i = 0; i < MAX_WORD_LENGTH; ++i)
    nword_length[i] = 0;

  wl = 0;
  state = OUT;
  while((c = getchar()) != EOF) {
    if(c == ' ' || c == '\t' || c == '\n')
      state = OUT;
    else
      state = IN;

    if(state == IN)
      ++wl;
    
    if(state == OUT && wl != 0) {
      if(wl <= MAX_WORD_LENGTH)
        ++nword_length[wl - 1];
      else
        ++nlong_words;
      wl = 0;
    }
  }

  printf("Length\tCount\n");
  for(i = 0; i < MAX_WORD_LENGTH; ++i)
    printf("%6d\t%5d\n", i + 1, nword_length[i]);
  printf("\nWords exceed length of %d: %d\n", MAX_WORD_LENGTH, nlong_words); */

/* #define IN 1
#define OUT 0 */

/*   int c, nl, nw, nc, state;

  nl = nw = nc = 0;
  state = OUT;
  while((c = getchar()) != EOF) {
    ++nc;
    if(c == '\n')
      ++nl;
    if(c == ' ' || c == '\t' || c == '\n')
      state = OUT;
    else if(state == OUT) {
      state = IN;
      ++nw;
    }
  }
  printf("w %d, c %d, l %d", nw, nc, nl); */

  /* int c, state;

  state = OUT;
  while((c = getchar()) != EOF) {
    if(c == ' ' || c == '\t' || c == '\n') {
      if(state != OUT) {
        state = OUT;
        putchar('\n');
      }
    } else
      state = IN;
    if(state == IN)
      putchar(c);
  } */

/*  int c, i, nwhite, nother;
 int ndigits[10];

 nwhite = nother = 0;
 for(i = 0; i < 10; ++i)
    ndigits[i] = 0;
  
  while((c = getchar()) != EOF) {
    if(c >= '0' && c <= '9')
      ++ndigits[c - '0'];
    else if(c == ' ' || c == '\t' || c == '\n')
      ++nwhite;
    else
      ++nother;
  }

  printf("digits =");
  for(i = 0; i < 10; ++i)
    printf(" %d", ndigits[i]);
  printf(", white space = %d, other = %d", nwhite, nother); */
