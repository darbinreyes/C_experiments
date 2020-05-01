// test printing an md5 hash value = 16 bytes.

#include <stdio.h>

void
print_16byte_hash(void) {
  unsigned long buf0  = 0x22AAFFAABBAACCAA;
  unsigned long buf1  = 0x1122334455667788;
  unsigned char bufa0[] = {0x22, 0xAA, 0xFF, 0xAA,0xBB,0xAA,0xCC,0xAA, 0x11, 0x22,0x33,0x44,0x55,0x66,0x77,0x88};

  printf("%.16lX\n", buf0);
  printf("%.16lX\n", buf1);
  printf("%.16lX  // %.16lX\n", *((unsigned long*)bufa0), *((unsigned long*)bufa0+1));

}

void
print_2byte_hash(void) {
  unsigned short buf  = 0x22AA;
  unsigned char bufa[] = {0x22, 0xAA};

  printf("%.4X\n", buf);
  printf("%.4X\n", *((unsigned short*)bufa));

}
int
main(void) {


  printf("Hello, string. sizeof(int) = %lu\n", sizeof(int));

  printf("%.*s\n", 3, "hello"); // cool. nice.
  print_2byte_hash();
  print_16byte_hash();

}