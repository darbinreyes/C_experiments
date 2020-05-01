#include <stdio.h>


int main(void) { // note that main has type int but doesn't return a value explicit
	int i;
	int *p;

	printf("hello order of eval.\n");


	p = &i;
	i = 7;

	printf("i = %d\n", *p++); // What will this print?

}

void exp0(void) {
	int i;
	int *p;

	p = &i;
	i = 7;

	printf("i = %d\n", *p++); // What will this print?
}


void exp1(void) {
	int i;
	int *p;

	p = &i;
	i = 7;

	printf("i = %d\n", *p++); // What will this print?
}