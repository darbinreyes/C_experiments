
#include <stdio.h>
void celtofar(void);
/* print Fahrenheit-Celsius table
for fahr = 0, 20, ..., 300; floating-point version */

int
main() {
	float fahr, celsius; float lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;
	/* lower limit of temperature scale */ /* upper limit */
	/* step size */
	fahr = lower;
	printf("|%-3s |%-6s|\n", "F", "C");
	while (fahr <= upper) {
		celsius = (5.0/9.0) * (fahr-32.0); 
		printf("|%3.0f |%6.1f|\n", fahr, celsius);
		fahr = fahr + step;
	}
	celtofar();
}

void celtofar(void) {
	float fahr, celsius; float lower, upper, step;

	lower = 0;
	upper = 300;
	step = 10;
	/* lower limit of temperature scale */ /* upper limit */
	/* step size */
	//fahr = lower;
	celsius = lower;
	printf("|%-3s |%-6s|\n", "C", "F");
	while (fahr <= upper) {
		//celsius = (5.0/9.0) * (fahr-32.0);
		fahr = (9.0/5.0) * celsius + 32.0;
		printf("|%3.0f |%6.1f|\n", celsius, fahr);
		celsius = celsius + step;
	}
}