#include <stdio.h>

/* char arr[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char (*daytab)[13] = (char (*)[13])arr; */
/* char *daytab[2] = {
  "\0\37\34\37\36\37\36\37\37\36\37\36\37",
  "\0\37\35\37\36\37\36\37\37\36\37\36\37",
}; */

int day_of_year(int y, int m, int d);
void month_day(int y, int d, int *pm, int *pd);

main() {
  int year = 2024, month = 2, day = 29;
  int yearday;
  printf("test day_of_year\n");
  printf("month %d, year %d day %d is year day %d\n",
    month, year, day, yearday = day_of_year(year, month, day));

  printf("test month_day\n");
  month_day(year, yearday, &month, &day);
  printf("year %d day %d is a month %d day %d\n",
    year, yearday, month, day);

  return 0;
}

char daytab[2][13] = {
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* No validty check */
int day_of_year(int year, int month, int day) {
  int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  char *pmd = *(daytab + leap);

  while(pmd - *(daytab + leap) + 1 < month)
    day += *pmd++;
  return day;
}

void month_day(int year, int day, int *pmonth, int *pday) {
  int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  char *p = *(daytab + leap);

  while(day > *p)
    day -= *p++;
  *pmonth = p - *(daytab + leap) + 1;
  *pday = day;
}
