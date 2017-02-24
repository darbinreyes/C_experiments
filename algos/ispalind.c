#include <stdio.h>
#include <stdlib.h> // for int const atoi(char *s)

int ispalind(int n);

int main(int argc, char *argv[]) {
	int n = 0;

	if(argc > 1) {
		n = atoi(argv[1]);
	}

	printf("Is the integer %d a decimal palindrome?\nHmmmm......\n", n);

	printf("%s\n", ispalind(n)? "Yes": "No");

	return 0;
}

#define MAX_N_DIGITS 40 // max number of digits allowed. 64 bits uses max of 20 digits but use 40 digits to be safe. 

int ispalind_array(int na[], int len);

int ispalind(int n) {
	int i = 0;
	int na[MAX_N_DIGITS];
	
	if(n < 0)
		n = -n; 

	while(n > 0 && i < MAX_N_DIGITS) {
		na[i] = n%10;
		n /= 10;
		i++;
	}

	return ispalind_array(na, i);
}

int ispalind_array(int na[], int len) {
	int i, j;

	for(i=0, j=len-1; i < len/2; i++, j--)
		if(na[i] != na[j])
			return 0;

	return 1;
}