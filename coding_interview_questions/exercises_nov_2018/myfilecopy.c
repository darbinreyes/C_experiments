// myfilecopy.c

#include <stdio.h>

// KNR-C 1.5.1
int main(int argc, char** argv) {
  int c;

  c = getchar();
  while(c != EOF) {
    putchar(c);
    c = getchar();
  }
}

