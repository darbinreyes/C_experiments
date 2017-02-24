#include <stdio.h>
#include <assert.h>
#include <ctype.h>


/*******************************************************************************

Exercise 5-6. Rewrite appropriate programs from earlier
chapters and exercises with pointers instead of array indexing. Good
possibilities include getline (Chapters 1 and 4), atoi, itoa, and their variants
(Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4).

******************************************************************************/

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

 #include <stdlib.h>

     int
     atoi(const char *str);


DESCRIPTION
     The atoi() function converts the initial portion of the string pointed to
     by str to int representation.

**/
/**

  Converts a string of decimal digits to an int.
  Conversion stops at the first non-digit.
  Leading '0' chars are ignored.
  No overflow protection if s is too big to fit in an int.
  returns 0 if the first char is not a digit.

  Assert if s is NULL.


**/
int atoi0(const char *s) {
  //design before u code bitch. on paper. aka think before u code fucker.
  int val = 0;

  // validate args.
  assert(s != NULL);

  while(isdigit(*s)) {
    val = val * 10 + (*s - '0');
    s++;
  }

  return val;
}

void reverse0(char *s);

/**
 itoa: convert i to characters in s

  Assert if s is NULL.

**/
void itoa(int i, char *s)
{
  char *t;
  int n;

  assert(s != NULL);

  t = s; // save pointer to start of s, we need to reverse s later.
  n = i;

  if(i == 0){ // handle 0
    *s = '0';
    *++s = '\0';
    return;
  }

  if(i < 0) // handle negative ints.
    i = -i;


  for(;i > 0; i/=10){
    *s = '0' + (char)(i % 10); // save each digit of i, read right to left
    s++;
  }

  if(n < 0) { // handle negative ints.
    *s++ = '-';
  }

  *s = '\0'; // terminate s and point to last digit.

  reverse0(t);

}

/**
  Reverse given string in place.

  Assert if s is NULL.

**/
void reverse0(char *s)
{
  char *t;
  char c;

  assert(s != NULL);

  if(*s == '\0')
    return;

  t = s; // save pointer to start of s

  while(*s != '\0') {
    s++;
  }

  s--;

  while (t < s) { // reverse s via swaps.
    c = *t;
    *t = *s;
    *s = c;
    t++;
    s--;
  }

}


/**

  writing a function strindex(s,t) that returns the position or index in the
  string s where the string t begins, or -1 if s does not contain t.
  Because C arrays begin at position zero, indexes will be zero or positive,
  and so a negative value like -1 is convenient for signaling failure.

  Assert if s or t is NULL.
  Returns -1 if t is not in s or if either s or t are empty. > 0 otherwise.

**/
size_t strindex0(const char *s, const char *t) {
  const char *ts, *tt, *ss;
  size_t i;

  assert(s != NULL && t != NULL);

  if(*s == '\0' || *t == '\0')
    return -1;

  ts = s;
  tt = t;

  while(*ts++ != '\0')
    ;

  while(*tt++ != '\0')
    ;

  //printf("%lu , %lu\n", ts - s, tt - t);

  if(ts - s < tt - t) // s is shorter than t
    return -1;

  ts = ts - (tt - t); // move ts back by len(t) chars.
  i = 0;

  //printf("%s , %s\n", s, ts);

  while(s <= ts) {
    tt = t;
    ss = s;
    while(*ss++ == *tt++) {
      if(*tt == '\0')
        return i;
    }
    i++;
    s++;
  }

  return -1;
}

#if 0

// my getop() see /Users/darbinreyes/dev/experiments/C/KNR_C/Chapter5/s5.5/reverse_polish_calculator.c

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


void test_atoi(void) {

  printf("%d.\n", atoi0("578"));
}

void test_itoa(void) {
  char s[100];

  itoa(537,s);

  printf("%s.\n", s);

  itoa(1,s);

  printf("%s.\n", s);

  itoa(0,s);

  printf("%s.\n", s);

  itoa(-99,s);

  printf("%s.\n", s);

  itoa(-0,s);

  printf("%s.\n", s);
}

void test_strindex(void) {
  size_t i;
  char *s = "hello, world";
  char *t = "wo";

  i = strindex0(s, t);

  printf("s = %s, t = %s. index = %lu. s[i] = %s.\n", s, t, i, s+i);

  s = "The C Programming Language.";
  t = "Language";

  i = strindex0(s, t);

  printf("s = %s, t = %s. index = %lu. s[i] = %s.\n", s, t, i, s+i);

  s = "The C Programming Language.";
  t = "Pro";

  i = strindex0(s, t);

  printf("s = %s, t = %s. index = %lu. s[i] = %s.\n", s, t, i, s+i);

  s = "The C Programming Language.";
  t = "The";

  i = strindex0(s, t);

  printf("s = %s, t = %s. index = %lu. s[i] = %s.\n", s, t, i, s+i);
}

#define MAX_LINE 100

void test_getline(void) {
  char s[MAX_LINE];
  size_t len;
  //knr_getline(s,MAX_LINE);
  len = my_getline(s,MAX_LINE);
  printf("hello....%s.... len=%lu\n", s, len);
}

int main(void) {
  //test_atoi();
  //test_itoa();
  //test_strindex();
  return 0;
}