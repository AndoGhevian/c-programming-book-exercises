#include <stdio.h>
#include <string.h>

int any(char s1[], char s2[]);

main() {
  int ci;

  char s1[100] = "123456789";
  char s2[100] = "abcd9cv5k34";

  ci = any(s1, s2); /* should return 2 (for digit 3)*/

  if(ci != -1)
    printf("string %s character %c occured" 
      " at\nindex %d of string %s\n", s2, s1[ci], ci, s1);
  else
    printf("No common characters of strings\n");

  printf("strbrk test: %s\n", strpbrk(s1, s2));

  char x[100] = "aaa";
  printf("%s   %s\n", x, strcat(x, "bb"));

  return 0;
}

int any(char s1[], char s2[]) {
  int i, j;

  for(i = 0; s1[i] != '\0'; ++i)
    for(j = 0; s2[j] != '\0'; ++j)
      if(s1[i] == s2[j])
        return i;

  return -1;
}
