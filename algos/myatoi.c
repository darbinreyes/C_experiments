#include <stdio.h>
#include <ctype.h>

int myatoi(char *s);

int main(int argc, char *argv[]){
	printf("myatoi = %d\n", myatoi("    -129   "));
	printf("myatoi = %d\n", myatoi("7"));
	printf("myatoi = %d\n", myatoi("18423"));
	printf("myatoi = %d\n", myatoi("101"));

}

// my implementation of atoi()
int myatoi(char *s) {
	int ival = 0, sign = 1;

	// move past any leading ws
	while(*s == ' ' || *s == '\t') 
		s++;

	// check for a minus sign

	if(*s == '-') {
		sign = -1;
		s++;
	}

	while(*s && isdigit(*s)){
		ival = (ival * 10) + *s - '0';
		s++;
	}

	return sign * ival;
}