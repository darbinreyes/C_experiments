// Convert a string to an integer.

#include <stdio.h>
#include <assert.h>

/*
  PLAN:
  No error handling to start.
  An integer in decimal can be expressed as a sum of a the digit times a power of ten.
  Since the first char is a the MSDigit, we can use the accumulation method to compute
  the integer value.
*/
int my_atoi(char *s) {
  int accum;
  assert(s != NULL);

  accum = 0;

  while(*s != '\0') {
    // Validation TODO: Check for non-digit chars.
    accum = (accum * 10 + *s++ - '0');
  }

  return accum;
}

/*

 Test case: *s="37";

*/


int main(void) {

  printf("Hello, atoi = %d.\n", my_atoi("37"));

  return 0;
}