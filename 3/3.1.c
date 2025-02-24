#include <stdio.h>

int binarysearch(int x, char arr[], int length);

main() {
  int x = 'B';
  char arr[11] = "ABCEFabcd";
  
  printf("result %d\n", binarysearch(x, arr, 10));
  printf(binarysearch(x, arr, 10) != -1
    ? "%c exist in string %s\n"
    : "%c not exist in string %s\n",
    x, arr);
  return 0;
}

/* Must provide incresing sorted array of chars */
int binarysearch(int x, char v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;

  while(low < high) {
    mid = (low + high) / 2;

    if(x > v[mid])
      low = mid + 1;
    else
      high = mid;
  }

  if(x == v[low])
    return low;

  return -1;
}

/* int binarysearch(int x, char v[], int n) {
  int low, high, mid;

  low = 0;
  high = n - 1;

  for(mid = (low + high) / 2; x != v[mid] && low < high; mid = (low + high) / 2)
    if(x < v[mid])
      high = mid - 1;
    else
      low = mid + 1;

  if(x == v[mid])
    return mid;

  return -1;
} */
