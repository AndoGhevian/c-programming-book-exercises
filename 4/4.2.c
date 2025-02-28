#include <stdio.h>
#include <ctype.h>
#include <float.h>
#include <math.h>

double atof(char s[]);

main() {
  char s[100] = "-123e-5";
  printf("string %s\nfloat %f\n", s, atof(s));
  
  return 0;
}

double atof(char s[]) {
  double val, power;
  int sign, i, fe, e, esign;
  for(i = 0; s[i] != '\0' && isspace(s[i]); i++);

  sign = 1;
  if(s[i] == '-')
    sign = -1;
  if(s[i] == '-' || s[i] == '+')
    i++;

  for(val = 0.0; s[i] != '\0' && isdigit(s[i]); val = val * 10.0 + s[i] - '0', i++);

  fe = 0;
  if(s[i] == '.')
    for(i++; s[i] != '\0' && isdigit(s[i]); val = val * 10.0 + s[i] - '0', i++, fe--);

  esign = 1;
  if(s[i] == 'e' || s[i] == 'E') {
    i++;
    if(s[i] == '-')
      esign = -1;
    if(s[i] == '-' || s[i] == '+')
      i++;
  }

  for(e = 0; s[i] != '\0' && isdigit(s[i]); e = e * 10 + s[i] - '0', i++);
  e = e * esign + fe;
  if(e < 0)
    esign = -1;
  else
    esign = 1;

  for(power = 1.0; e != 0; e -= esign)
    power *= 10;

  return sign * ((esign < 0) ? val / power : val * power);
}
