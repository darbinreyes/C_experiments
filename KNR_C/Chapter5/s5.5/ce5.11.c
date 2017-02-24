#include <stdio.h>


int main(int argv,char *arg[]) {
  int c;
  int ns = 4;

  // detab
  while((c = getc(stdin)) != EOF) {
    if(c != '\t')
      putc(c, stdout);
    else
      while(ns-- > 0)
        putc(' ', stdout);

    ns = 4;
  }

}