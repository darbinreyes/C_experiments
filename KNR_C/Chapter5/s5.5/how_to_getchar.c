#include <stdio.h>

void how_to_use_getchar0(void) {
  int c;

  /**

   When you execute, pauses execution, at this point you can type arbitrary amounts
   of human readable text (alphanumeric + punctuation), when your done with that
   you press the "enter" key which tells getchar() to unpause execution.
   At that point stdin is filled with everything you typed in. Your first call
   to get char will return the first char you typed in. Another call to getchar
   will return the second char you typed. You can get all the chars you typed into
   stdin by calling getchar until it returns EOF.

  **/
  c = getchar();

  // write the first char from stdin to stdout
  putc(c,stdout);
  // write new line.
  putc('\n', stdout);
}

void how_to_use_getchar1(void) {
  int c;

  /**

   When you execute, pauses execution, at this point you can type arbitrary amounts
   of human readable text (alphanumeric + punctuation), when your done with that
   you press the "enter" key which tells getchar() to unpause execution.
   At that point stdin is filled with everything you typed in. Your first call
   to get char will return the first char you typed in. Another call to getchar
   will return the second char you typed.

  **/
  c = getchar();

  // write the first char from stdin to stdout
  putc(c,stdout);
  // write new line.
  putc('\n', stdout);

  //second char
  c = getchar();
  putc(c,stdout);
  putc('\n', stdout);
}

void how_to_use_getchar2(void) {
  int c;

  /**

   To get multiple chars you can call getchar in a loop until you get the special
   char EOF but you can condition the loop to terminate on any char.

  **/
  while ((c = getchar()) != EOF) { //type control+D to insert an EOF, control+Z kills the program.
    // write the first char from stdin to stdout
    putc(c, stdout);
  }


  // write new line.
  //putc('\n', stdout);
}

int main(void) {
  //how_to_use_getchar0();
  how_to_use_getchar1();
}