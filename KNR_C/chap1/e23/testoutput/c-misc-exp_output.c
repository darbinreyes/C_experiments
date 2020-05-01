#include <stdio.h>

void str_constant_var(void);
void formating_prints(void);
void machine_dependent_sign_mod(void);
void sizeof_no_parens(void);
void escape_chars_and_constants(void);
void comment_in_expression(void);

int main (void) {

	
	
	
	
	
	comment_in_expression();
	return 0;
}

#define MY_STR_CONST_HELLO "hello"  

void str_constant_var(void) {
	char *a = "hello";
	char b[] = "hello";
	char c[] = MY_STR_CONST_HELLO;
	printf("a) %s world.\n", a);
	
	printf("yoyoma plays the %s.\n", a);

	printf("b) %s world.\n", b);
	b[0] = 'c'; 
	printf("yoyoma plays the %s.\n", b);

	printf("c) %s world.\n", c);
	c[0] = 'c'; 
	printf("yoyoma plays the %s.\n", c);
}

#define MY_STR_FMT_STRING "HTTP status code = %3d"

void formating_prints(void) {

	printf("Print an int = %d\n",  100);
	printf("Print an int = %6d\n", 100); 
	printf("Print an int = %2d\n", 100); 
	printf("Print an int = %2d\n", 1000000);
 

	char fmt_str[] = "%3d"; 
	printf("sizeof(fmt_str) = %lu\n", sizeof(fmt_str)); 
	
	printf("sizeof(MY_STR_FMT_STRING) = %lu \n", sizeof(MY_STR_FMT_STRING)); 
	
	static char fstr[sizeof(MY_STR_FMT_STRING)];
    printf("sizeof(fstr) = %lu \n", sizeof(fstr)); 

	int http_status = 204; 
	sprintf(fstr, MY_STR_FMT_STRING, http_status);
	printf("%s\n", fstr);
}

void machine_dependent_sign_mod(void) {
	int n = 114;

	
	

	printf("%d mod 10 = %d , %d mod -10 = %d\n", n, n%10, n, n%-10);
}

void sizeof_no_parens(void) {
	int n;
	printf("size of no paren = %lu", sizeof n); 
}

void escape_chars_and_constants(void) {
	char tmp[] = "\n \t \\ \' // ";
	char c = '\'';
	char a = '\"';
	char c2 = '"'; 
	char s[] = " 'hello' \"";
	printf("%s\n",s);
}

void comment_in_expression(void){
	int i = 0;

	i = i + 1; 
	
	i = 4; 
	i=5; 
	printf("yo\n");
}