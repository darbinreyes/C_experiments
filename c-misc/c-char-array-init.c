#include <stdio.h>

int
main() {

/* Question START
 Can you avoid using ZeroMem() to iniatilize a char. array with zeros
 by initializing it to {'0'} as with structures?
 Answer: Yes
*/
char a[10] = {'0'};
// Question END

/* Question START

  Is this really true? KNR 4.9.
  "
  char pattern = "ould";
  is a shorthand for the longer but equivalent
  char pattern[] = { 'o', 'u', 'l', 'd', '\0' };
  "
  Answer: NO, you get a compiler warning.

c-char-array-init.c:25:6: warning: incompatible pointer to integer conversion
      initializing 'char' with an expression of type 'char [5]'
      [-Wint-conversion]

  KNR meant char pattern[] = "ould";

*/

// char a2 = "YOLO"; // generates compiler warning.
  char a3[] = "YOLO";

}