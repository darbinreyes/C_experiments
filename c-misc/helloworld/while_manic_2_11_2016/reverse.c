#include <stdio.h>
#include <assert.h>

char *reverse(char *s) {
  char *t; // pointer to end
  char c; // temp for char swap
  char *ss; // pointer to start

  // arg. valid check.
  assert(s != NULL);

  /* set pointer to end , then swap until center char.*/
  ss = s;
  t = s;

  while(*t != '\0') // set pointer to end
    t++;

  t--; // point to last char
  printf("s = %s.\n", s);

  printf("t = %c.\n", *t);

  assert(t >= s);
  // swap
  while(s < t) {
    // swap
    c = *t; // t to c

    //printf("c = %c.\n", *t);
    //printf("c = %c.\n", c);
    //printf("s = %c.\n", *s);

    *t = *s; // s to t


    *s = c; // t to s

    s++;
    t--;
  }

  return ss;
}

int main(void) {
  char str[] = "hello";
  char *s = str;

  printf("s = %s.\n", s);

  reverse(s);

  printf("s reversed = %s.\n", s);

  return 0;
}