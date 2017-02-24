#include <stdio.h>

typedef void (*TEST_FUNC)(int a);

typedef
struct _test_protocol {
  TEST_FUNC test0;
  TEST_FUNC test1;
} test_protocol;

typedef
struct _test_protocol_main {
  test_protocol *p0;
  test_protocol *p1;
  struct __something {
    int a;
    int b;
  } s0;
  struct __something s1;
} test_protocol_main;

GetVariable2 (

gRT->SetVariable(

EFI_VARIABLE_NON_VOLATILE