#include <stdio.h>

int
main() {
// char *c[]; 
/*
c-arrays.c:5:7: error: definition of variable with array type needs an explicit
      size or an initializer
char *c[];
      ^
1 error generated.
*/
printf("hello, "); printf("world"); printf("\n");

/* Question START
 Question: Can you avoid using ZeroMem() to iniatilize a char. array with zeros
 by initializing it to {'0'} as with structures?
 Answer: Yes
*/

// Question END

}