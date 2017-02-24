#include <stdio.h>

void str_constant_var(void);
void formating_prints(void);
void machine_dependent_sign_mod(void);
void sizeof_no_parens(void);
void escape_chars_and_constants(void);
void comment_in_expression(void);

int main (void) {

	//str_constant_var();
	//formating_prints();
	//machine_dependent_sign_mod();
	//sizeof_no_parens();
	//escape_chars_and_constants();
	comment_in_expression();
	return 0;
}

#define MY_STR_CONST_HELLO "hello"  

void str_constant_var(void) {
	char *a = "hello";
	char b[] = "hello";
	char c[] = MY_STR_CONST_HELLO;
	printf("a) %s world.\n", a);
	//a[0] = 'c'; // ERROR is Bus Error 10. 
	printf("yoyoma plays the %s.\n", a);

	printf("b) %s world.\n", b);
	b[0] = 'c'; // OK!
	printf("yoyoma plays the %s.\n", b);

	printf("c) %s world.\n", c);
	c[0] = 'c'; // OK 2! 
	printf("yoyoma plays the %s.\n", c);
}

#define MY_STR_FMT_STRING "HTTP status code = %3d"

void formating_prints(void) {

	printf("Print an int = %d\n",  100);
	printf("Print an int = %6d\n", 100); // 3 space pad before the 100. 
	printf("Print an int = %2d\n", 100); // This won't truncate the int. , %2d means use AT LEAST 2 positions NOT only 2 positions. 
	printf("Print an int = %2d\n", 1000000);
/*
Print an int = 100
Print an int =    100
*/ 

	char fmt_str[] = "%3d"; // sizeof(fmt_str) == 2?
	printf("sizeof(fmt_str) = %lu\n", sizeof(fmt_str)); // NO! sizeof(fmt_str) == 4!!!!!!!!!! The % and d are separate chars. only the print function knows it is a place holder for a single argument. 
	//int sprintf(char *string, char *format, arg1, arg2, ...);
	printf("sizeof(MY_STR_FMT_STRING) = %lu \n", sizeof(MY_STR_FMT_STRING)); //expect 23
	
	static char fstr[sizeof(MY_STR_FMT_STRING)];
    printf("sizeof(fstr) = %lu \n", sizeof(fstr)); //expect 23

	int http_status = 204; 
	sprintf(fstr, MY_STR_FMT_STRING, http_status);
	printf("%s\n", fstr);
}

void machine_dependent_sign_mod(void) {
	int n = 114;

	// K&R 2.5 Arithmetic operators
	/*
		The direction of truncation for / and the sign of the result for % are 
		machine-dependent for negative operands, as is the action taken on 
		overflow or underflow.
	*/

	printf("%d mod 10 = %d , %d mod -10 = %d\n", n, n%10, n, n%-10);
}

void sizeof_no_parens(void) {
	int n;
	printf("size of no paren = %lu", sizeof n); // it works! dont forget to match the format str to the type!! you asshole
}

void escape_chars_and_constants(void) {
	char tmp[] = "\n \t \\ \' // ";
	char c = '\'';
	char a = '\"';
	char c2 = '"'; // this is allowed
	char s[] = " 'hello' \"";
	printf("%s\n",s);
}

void comment_in_expression(void){
	int i = 0;

	i = i + /* is this legal ? */1; // yes, it is legal.
	//i = 3; /* what about this? *                   / nope, this one isn't legal.
	i = 4; // hello \
	bro
	i=5; // ohh shit, bro above is legal.
	printf("yo\n");
}