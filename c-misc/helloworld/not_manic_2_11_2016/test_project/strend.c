#include <stdio.h>

int strend(char *s, char *e) {
  char *ts, *te;

  if(s == NULL || e == NULL )//|| *s == '\0' || *e == '\0')
    return -1;

  ts = s;
  te = e;

  while(*ts++ != '\0')
    ;

  while(*te++ != '\0') // the increment of te still takes place when the test hits the '\0'
    ;

  //printf("e = %p , te = %p. te - e = %ld.\n", e, te, te - e);
// Question: if e is empty string will te be incremented? Guess= yes it will be incremented. The function will compare 'e' to the '\0' of string pointed to by e then return false.
//
  if(ts - s < te - e)
    return 0;

  ts -= te - e;
  te = e;

  while(*ts == *te) {
    if(*ts == '\0')
      return 1;
    ts++;
    te++;
  }

  return 0;
}

#if 0
int main(void) {
  char *s = "even when i lie";
  char *e = "";

  printf("s = %s, e = %s, strend() = %d.\n", s, e, strend(s, e));
  return 0;
}
#endif