#include <stdio.h>

// bitwise rotate i by n bits. n < 0 means rotate right. return i after rotation.

#define LSB (1)
#define MSB (~( ((unsigned)-1) >> 1)) // try casting -1U
int bitRotate(int i, int n) {
  int t, right;

  if(i == 0 || i == -1 || n == 0)
    return i;

  t = 0; // tmp that stores the bit the was shifted out of i.

  right = n < 0;

  if(right) // shifting by a negative number is illegal in C
    n = -n;

  while(n--) {
    if(right) {
      t = i & LSB;
      i = ((unsigned)i) >> 1; // cast to ensure a 0 is shifted in.

      if(t)
        i |= MSB;

    } else { // left shift
      t = i & MSB;
      i <<= 1;
      if(t)
        i |= LSB;
    } // else
  } // while


  return i;
}

int main(int argc, char **argv) {
  // test bitRotate
  int in, out_expected, out, n;

  // test 1
  in = -1;
  n = 10;
  out_expected = -1;
  out = bitRotate(in, n);
  // use ctest!!!
  printf("%o out == %o out_expected ? %d.\n",out, out_expected, out == out_expected);

  // test 2
  in = 0;
  n = -13;
  out_expected = 0;
  out = bitRotate(in, n);
  // use ctest!!!
  printf("%o out == %o out_expected ? %d.\n",out, out_expected, out == out_expected);

  // test 3
  in = ~077; // ...11000000
  n = 1;
  out_expected = 0x0FFFFF81;//~0176; // 1 1000 0001 == F81
  out = bitRotate(in, n);
  // use ctest!!!
  printf("in == %o, %o out == %o out_expected ? %d.\n", in, out, out_expected, out == out_expected);
  return 0;
}