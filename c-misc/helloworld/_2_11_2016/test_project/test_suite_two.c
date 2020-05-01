#include "seatest.h"

int strend(char *s, char *e);

#if 0
void test_asserting()
{
	assert_true( 1 == 1);
	assert_false(1 == 2);
	assert_int_equal(1, 1);
}

void test_assert_fails()
{
	assert_true( 1 == 2);
}
#endif

void test_strend()
{
  assert_true(strend("This is the sentence", "sentence"));
  assert_false(strend("hello", "jello"));
}

void test_fixture_two( void )
{
	test_fixture_start();
	run_test(test_strend);
	test_fixture_end();	
}