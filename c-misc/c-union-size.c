#include <stdio.h>
/*

 Test to see what sizeof() returns for a union member.
 Does it return the of the union or the size of the members type(I expect sizeof member type).

*/

#pragma pack(1)

typedef struct {
  int  x;
  int  y;
  char z;
} MY_STRUCT; // sizeof(int)*2 +sizeof(char)

typedef struct {
  short  a;
  short  b;
  char   c:4;
  char   d:4;
} MY_STRUCT2; // sizeof(short)*2 + sizeof(char)

typedef union {
  MY_STRUCT  m1;
  MY_STRUCT2 m2;
} MY_UNION;

#pragma pack()

int main(void) {

  MY_UNION mu;

  printf("sizeof(int) = %zd . Expect 4.\n", sizeof(int));
  printf("sizeof(short) = %zd . Expect 2.\n", sizeof(short));
  printf("sizeof(MY_STRUCT) = %zd . Expect 9.\n", sizeof(MY_STRUCT));
  printf("sizeof(MY_STRUCT2) = %zd . Expect 5.\n", sizeof(MY_STRUCT2));
  printf("sizeof(mu) = %zd . Expect 9.\n", sizeof(mu));
  printf("sizeof(mu.m1) = %zd . Expect 9.\n", sizeof(mu.m1));
  printf("sizeof(mu.m1) = %zd . Expect 5.\n", sizeof(mu.m2));

  return 0;
}