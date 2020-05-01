#include <stdio.h>
#include <assert.h>

//// idea : use seatest to unit test my answers. would look awesome on github.

/**

Exercise 5-6. Rewrite appropriate programs from earlier
chapters and exercises with pointers instead of array indexing. Good
possibilities include getline (Chapters 1 and 4), atoi, itoa, and their variants
(Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4).

**/

/**

 #include <stdlib.h>

     int
     atoi(const char *str);


DESCRIPTION
     The atoi() function converts the initial portion of the string pointed to
     by str to int representation.

**/

int my_atoi(const char *s) {
  //design before u code bitch. on paper. aka think before u code fucker.
  int val = 0;
  assert(s != NULL);

  while(isdigit(*s)) {
    val = val + (*s - '0') * 10;
  }

  val /= 10;

  return val;
}

#if 0
int mysum(int val, const char *s){
return 0;
}


/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
}
#endif

/* ##### COPIED FROM K&R page 30 just added my comments. getline: read a line into s, return length */
int knr_getline(char s[],int lim)
{
  int c, i;

  // Copy up to < lim-1 chars. (-1 b/c we need space for the newline AND null terminator .). e.g if lim = 3, then lim-1==2, the iteration will only run for i=0 < 2, i=1 < 2, NOT  i=2 < 2
  // Stop copying if you copy lim-1 chars cuz we can't fit more.
  // Also stop copying if we get an EOF char.(so potentially there is no new line on the input) or a newline char.
  for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) // i < lim stops i at last char so lim-1 is right before that.
    s[i] = c;

  // if we stopped at a new line we know, we didn't stop at an EOF.
  if (c == '\n') { // this will never be true if the for loop terminates on the i < lim-1 condition. Becuase the assignment of c would not occur (short circuit logical operators). Thus in this case when the loop terminates c will contain the char value of the previous iteration which could not be the new line char. But if we assume it where the new line char, then the loop would have terminated at the previous iteration. i=1
    s[i] = c;
    ++i;
  }

  s[i] = '\0';
  return i;
}

size_t my_getline(char *s,const int lim)
{
  char c;
  char *t;
  t=s;
  printf("Type something bro:\n");
  assert(lim != 0);
  while(s < (s+lim-1) && (c=getchar()) != EOF && c!='\n')
    *s++ = c;

  if(c == '\n')
    *s++ = c;

  *s = '\0';
  return (size_t)(s-t);
}

/**
  writing a function strindex(s,t) that returns the position or index in the string s where the string t begins, or -1 if s does not contain t. Because C arrays begin at position zero, indexes will be zero or positive, and so a negative value like -1 is convenient for signaling failure.
**/
size_t strindex(const char *s, const char *t) {

return 0;
}

#if 0
/* getop: get next character or numeric operand */ int getop(char s[])
{
int i, c;
while ((s[0] = c = getch()) == ' ' || c == '\t') ;
s[1] = '\0';
if (!isdigit(c) && c != '.')
return c; /* not a number */ i = 0;
if (isdigit(c)) /* collect integer part */ while (isdigit(s[++i] = c = getch()))
;
if (c == '.') /* collect fraction part */
while (isdigit(s[++i] = c = getch())) ;
       s[i] = '\0';
       if (c != EOF)
           ungetch(c);
       return NUMBER;
}
#endif

#define MAX_LINE 100

void test_atoi(void) {
  my_atoi("578")
  printf("%d.\n")
}

void test_getline(void) {
  char s[MAX_LINE];
  size_t len;
  //knr_getline(s,MAX_LINE);
  len = my_getline(s,MAX_LINE);
  printf("hello....%s.... len=%lu\n", s, len);
}

int main(void) {
  test_atoi();
  return 0;
}