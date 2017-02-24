#include <stdio.h>


int main(void) {

  struct {
    unsigned int f0:1;
    unsigned int f1:1;
    unsigned int f2:1;
  } my_bit_field_struct;

  printf("struct size = %lu, int size = %lu.\n", sizeof(my_bit_field_struct), sizeof(int));

  /*

  struct size = 4, int size = 4.

  Lesson of this test:

  The compiler will try to pack the bit fields into a minimum number of bytes.


  */
}