#include <stdio.h>

enum {
	x = 0,
	y = 0xFFFFFFFF00000000
	//z = 0x1FFFFFFFF00000000
} foo;

enum {
	a
} bar;

int main(void) {

	printf("sizeof(foo) = %lu\n", sizeof(foo));

	printf("sizeof(bar) = %lu\n", sizeof(bar));

	int i = 0xDEADBEEF;
	char k = 0;

	k = i;
	i = k;
	printf("i = %x, sizeof(i) = %lu\n", i, sizeof(i));
	printf("k = %x, sizeof(k) = %lu\n", k, sizeof(k));
	//int32_t i = y;

	//printf("i = %x\n", i);

	return 0;
}