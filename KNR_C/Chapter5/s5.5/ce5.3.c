#include <stdio.h>
/**

Exercise 5-3. Write a pointer version of the function strcat that we showed in Chapter 2:
strcat(s,t) copies the string t to the end of s.

**/
/* strcat: concatenate t to end of s; s must be big enough */ 
void strcat0(char s[], char t[])
{
  int i, j;
  i = j = 0;
  while (s[i] != '\0') /* find end of s */
  i++;
  while ((s[i++] = t[j++]) != '\0') /* copy t */
  ;
}

void strcat1(char *s, char *t)
{
  while (*s != '\0') /* find end of s */ // *(s++) != '\0'
    s++;

  while ((*s++ = *t++) != '\0') /* copy t */
   ;
}


void
test(void) {
  char s[100] = "hello, world";
  char t[]    = " and goodnight.";

  printf("%s\n", s);
  strcat1(s, t);
  printf("%s\n", s);
}


int
main(void) {
  test();
  return 0;
}