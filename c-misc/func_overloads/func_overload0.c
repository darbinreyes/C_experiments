#include "func_overload.h"


void test(int a) {
  printf("hello world %d\n", a);
}

test_protocol p = {
  test,
  test
};

test_protocol p2;

test_protocol_main pmain = {
  &p,
  &p2,
  {
    2,
    4
  },
  {
    5,
    7
  }
};

int main (void) {
    pmain.p0->test0(0);
    pmain.p0->test1(1);
    pmain.p1->test0(0);
    pmain.p1->test1(1);
    //testyo(5);
    return 0;
}


