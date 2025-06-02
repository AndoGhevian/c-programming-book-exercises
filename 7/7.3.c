void minprintf(char *fmt, ...);

main() {
  minprintf("hel%%%dlo%wor%*.*dld\n", 10, 10, 5, 101);
  minprintf("hel%%%dlo%wor%*.4dld\n", 10, 6, 234);
  minprintf("hello%6.*s --- Yes: %d%% \n", 5, "world", 100);
  minprintf("invalid conversion specs: %123asd %*asd %.12ws %.*\n");
  minprintf("short me: %.*s\n", 7, "short Text");
  return 0;
}

#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

/* minimum 7 for format "%-*.*d" */
#define NSPEC 1000
char convspec[NSPEC];
int convspecarg[2];

#define is_convspecend(ptr) (ptr == convspec + NSPEC - 1)

void minprintf(char *fmt, ...) {
  int i, ispecarg;
  char *p, *specptr;

  int specarg1, specarg2;

  va_list ap;
  va_start(ap, fmt);

  #define scan_num_or_plc() {\
    if(*p == '*' && !is_convspecend(specptr)) {\
      *specptr++ = *p++;\
      ispecarg++;\
    }\
    else\
      while(isdigit(*p) && !is_convspecend(specptr))\
        *specptr++ = *p++;\
  }

  #define argparse(specargscount, convtype) {\
    if(specargscount == 0)\
      printf(convspec, va_arg(ap, convtype));\
    else if(specargscount == 1) {\
      specarg1 = va_arg(ap, int);\
      printf(convspec, specarg1, va_arg(ap, convtype));\
    }\
    else if(specargscount == 2) {\
      specarg1 = va_arg(ap, int);\
      specarg2 = va_arg(ap, int);\
      /* arguments in function arguments list are calculated in arbitarary order,
        so it is required to extract them in separate statements.
      */\
      printf(convspec, specarg1, specarg2, va_arg(ap, convtype));\
    }\
  }

  for(p = fmt; *p; p++) {
    for(i = 0; i < NSPEC && convspec[i] != '\0'; i++)
      putchar(convspec[i]);
    convspec[0] = '\0';

    if(*p != '%')
      putchar(*p);
    else {
      specptr = convspec;
      *specptr++ = *p++; /* % */
      ispecarg = 0;

      if(*p == '%') {
        *specptr = '\0';
        continue;
      }

      if(*p == '-' || *p == '+')
        *specptr++ = *p++;

      scan_num_or_plc();
      if(is_convspecend(specptr)) {
        p--;
        *specptr = '\0';
        continue;
      }

      if(*p == '.') {
        *specptr++ = *p++;

        scan_num_or_plc();
        if(is_convspecend(specptr)) {
          p--;
          *specptr = '\0';
          continue;
        }
      }

      *specptr++ = *p;
      *specptr = '\0';

      switch(*p) {
        case 'd':
        case 'i':
          argparse(ispecarg, int);
          convspec[0] = '\0';
          break;
        case 's':
          argparse(ispecarg, char *);
          convspec[0] = '\0';
          break;
        default:
          break;
      }
    }
  }

  va_end(ap);
}
