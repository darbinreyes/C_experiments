#include <stdio.h>

int
main(void) {
	/* Can you declare an array if length 0?
	ANS: Yes, you can! */

	int f[0];

	printf("Foo who? sizeof(f) = %lu\n", sizeof(f));
}