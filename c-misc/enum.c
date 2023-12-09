#include <stdio.h>

enum {
	x = 0,
	y = 0xFFFFFFFF00000000
} foo;

enum {
	z
} bar;

int main(void) {

	printf("sizeof(foo) = %lu\n", sizeof(foo));

	printf("sizeof(bar) = %lu\n", sizeof(bar));

	return 0;
}