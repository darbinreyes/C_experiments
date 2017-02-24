#include "func_overload.h"

static
void test(int a){
  printf("yo bro %d\n", a);
}

test_protocol p2 = {
  test,
  test
};

void testyo(int a){
  printf("fomo %d\n", a);
}