#include <stdio.h>
#include <string.h>

static void qsort(char v[], int left, int right);

main() {
  char s[] = "abcdeABCDEaasda";
  printf("%s sorted ", s);
  qsort(s, 0, strlen(s) - 1);
  printf("%s\n", s);

  return 0;
}

static void swap(char v[], int i, int j);
/* quick sort in incressing order */
void qsort(char v[], int left, int right) {
  int i, last;

  if(left >= right)
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for(i = left + 1; i <= right; i++)
    if(v[i] < v[left])
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

static void swap(char v[], int i, int j) {
  int temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
