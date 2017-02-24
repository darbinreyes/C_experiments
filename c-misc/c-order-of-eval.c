#include <stdio.h>

void exp0(void) {
	int i;
	int *p;

	p = &i;
	i = 7;
  printf("B: p = %p\n", p);
	printf("i = %d\n", *p++); // What will this print? The bug is that the post-increment will change the address of p to some random address. BUG!
	printf("A: p = %p. Expect p+sizeof(int)=%lu.\n", p, sizeof(int));
}


void exp1(void) {
	int i;
	int *p;

	p = &i;
	i = 7;

	printf("i = %d\n", *p++); // What will this print?
}

int main(void) { // note that main has type int but doesn't return a value explicit
	int i;
	int *p;

	printf("hello order of eval.\n");


	p = &i;
	i = 7;

	printf("i = %d\n", *p++); // What will this print? ANS: It will print 7. BUT note that there is a bug. See exp0().
	exp0();
}

