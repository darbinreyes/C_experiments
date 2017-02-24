#include <stdio.h>

void squeeze(char *s, char c) {
  char *t;

  if(s == NULL || c == '\0')
    return;

  t = s;

  while(*s != '\0') {
    if(*t == c)
      t++;
    else {
      *s = *t;
      if(*t == '\0')
        break;
      s++;
      t++;
    }
  }

  return;
}


int main(void) {
  char s[] = "jelloellow";
  char c = 'l';

  printf("s = %s. c = %c.\n", s, c);
  squeeze(s,c);
  printf("squeezed = %s.\n",s);
}