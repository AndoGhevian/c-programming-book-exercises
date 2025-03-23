#include <stdio.h>

int day_of_year(int y, int m, int d);
int month_day(int y, int d, int *pm, int *pd);

main() {
  int vc;
  /*modify this values and get 2 outputs: for current month day, and for the next day of year */
  int year = 2025, month = 11, day = 30;
  int yearday;

  printf("test day_of_year function\n");
  printf("day of the month %d, year %d, day %d is year day: %d\n",
    month, year, day, yearday = day_of_year(year, month, day));
  printf("\n");

  printf("test month_day function\n");
  vc = month_day(year, yearday + 1, &month, &day);
  if(vc != 0)
    return 1;

  printf("year %d day %d is a month %d day %d\n",
    year, yearday + 1, month, day);
  printf("\n");

  return 0;
}

char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
  int i, leap;

  if(year <= 0 || month <= 0 || day <= 0) {
    printf("year, month, day must be positive integers\n");
    return -1;
  }

  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  if(month > 12) {
    printf("month must be between 1 and 12\n");
    return -2;
  }
  
  if(day > daytab[leap][month]) {
    printf("invalid day %d of month %d, year %d (%d days)\n",
      day, month, year, daytab[leap][month]);
    return -3;
  }

  for(i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}

int month_day(int year, int day, int *pmonth, int *pday) {
  int iday, imonth, leap;
  
  if(year <= 0 || day <= 0) {
    printf("year, day must be positive integers\n");
    return -1;
  }

  leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
  for(iday = day, imonth = 1; imonth <= 12 && iday > daytab[leap][imonth]; imonth++)
    iday -= daytab[leap][imonth];

  if(imonth > 12) {
    printf("invalid day %d of year %d (days: %d)\n",
      day, year, day - iday);
    return -2;
  }

  *pday = iday;
  *pmonth = imonth;
  return 0;
}
