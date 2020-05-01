// Implementation of Euclid's algorithm
// i.e. to compute the greatest common divisor of two integers.
/*

This proposition assumes that 1 is the result of an antenaresis process.
Antenaresis, also called the Euclidean algorithm, is a kind of reciprocal
subtraction. Beginning with two numbers, the smaller, whichever it is, is
repeatedly subtracted from the larger.

*/
#include <stdio.h> // printf()
#include <stdlib.h> // atoi()
#include <assert.h>

/*
 VII.1.
 Given integers a and b
 If this algorithm returns 1, then a and b "are prime to one another".

 i.e. a and b are measured by unit alone as a common measure.
 i.e. their only common divisor is 1.
*/
int antenaresis (int a, int b) {
  assert(a > b & b > 1); // "When two unequal numbers are set out"
  int r = 0;

  do {
    a = a - b; // "and the less is continually subtracted in turn from the greater"
    // The proof is not difficult.
    // It depends on the observation that if b divides (that is, measures) both c and d, then b divides their difference c – d.
    r = a; // if the number which is left

    if (a < b) { // a == a % b.
      a = b;
      b = r;
    }

  } while (r > 1);

  return r; // 1 means a and b are prime to one another.
}

int main(int argc, char **argv) {
  int a = 0, b = 0;
  int r = 0;

  if (argc != 3) { // Enforce input format
    printf("Try again. Example: \"./a.out integer integer\"\n");
    return 0;
  }

  assert(argc == 3);

  a = atoi(argv[1]); // Get input values. Convert string to int.
  b = atoi(argv[2]);

  printf("Computing Euclidian Algorithm (%d, %d)\n", a, b);

  r = antenaresis (a, b);
  printf("Euclidian Algorithm (%d, %d) = %d.\n", a, b, r);
  return 0;
}


