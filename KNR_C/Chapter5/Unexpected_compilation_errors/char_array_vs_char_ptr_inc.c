#include <stdio.h>

void test0(void) {
  char s[] = "1 2 - 4 5 + *\n";

  while(*s != '\0') {
    putc(*s, stdin);
    #if 0
    s++;
    #endif
    //((char *)s)++; // also doesn't work.
  }
/**WTF
: error: cannot increment value of type
      'char [14]'
    s++;
    ~^
1 error generated.
**/
}


void test1(void) {
  char s[] = "1 2 - 4 5 + *\n";
  char *t = s;

  while(*t != '\0') {
    putc(*t, stdout);
    t++;
  }

}

void test2(void) {
  char s[] = "1 2 - 4 5 + *\n";
  char i = 0;

  while(s[i] != '\0') {
    putc(s[i], stdout);
    i++;
  }

}

int main(void) {
  //test0();
  test1();
  test2();
}