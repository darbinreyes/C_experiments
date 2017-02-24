#include <stdio.h>
#include <assert.h>

/**


Exercise 5-9. Rewrite the routines day_of_year and month_day with pointers instead of indexing.


**/
#define NUMCOLS 13
#define NUMROWS 2
static char daytab[NUMROWS][NUMCOLS] = {
{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};


/* day_of_year: set day of year from month & day */

int day_of_year(int year, int month, int day)
{
  int i, leap;

  if(year < 0 || month <= 0 || month > 12|| day <= 0 || day > 31)
    return -1;

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;


  for (i = 1; i < month; i++)
    day += *(*(daytab + leap) + i);

  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
  int i, leap, maxyd;

  assert(pmonth != NULL && pday != NULL);

  if(year < 0 || yearday <= 0 || pmonth == NULL || pday == NULL) {
    *pmonth = -1;
    *pday   = -1;
    return;
  }


  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;


  for (maxyd = 0, i = 1; i < 13; i++)
    maxyd += *(*(daytab + leap) + i); // daytab[leap][i];

  if(yearday > maxyd){
    *pmonth = -1;
    *pday   = -1;
    return;
  }


  for (i = 1; yearday > daytab[leap][i]; i++)
      yearday -= *(*(daytab + leap) + i);//daytab[leap][i];

  *pmonth = i;

  *pday = yearday;

}

int main(void) {
  int m, d;

  month_day(1988, 60, &m, &d);
  printf("month = %d, day = %d\n", m, d);

  d = day_of_year(1988, 2, 15);
  printf("day of year = %d\n", d);

}