#include <stdio.h>
#include <string.h>
#include <assert.h>

/**


Exercise 5-5. Write versions of the library functions strncpy, strncat, and
strncmp, which operate on at most the first n characters of their argument
strings. For example, strncpy(s,t,n) copies at most n characters of t to s. Full
descriptions are in Appendix B.

"char *strncpy(s,ct,n) copy at most n characters of string ct to s; return s.
"Pad with '\0''s if ct has fewer than n characters. // got missing info. on the
"function from http://linux.die.net/man/3/strncpy


" from bash "man strncpy"
strncpy() functions copy at most n characters from src
     into dst.  If src is less than n characters long, the remainder of dst is
     filled with `\0' characters.  Otherwise, dst is not terminated.
"

**/


/**

char *strncat(s,ct,n)

concatenate at most n characters of string ct to string s, terminate s with '\0'; return s.


**/


/**

There are two groups of string functions defined in the header <string.h>. The
first have names beginning with str; the second have names beginning with mem.
Except for memmove, the behavior is undefined if copying takes place between
overlapping objects.

*******Comparison functions treat arguments as unsigned char arrays.

In the following table, variables s and t are of type char *; cs and ct are of type const char
*; n is of type size_t; and c is an int converted to char.

int strncmp(cs,ct,n)
compare at most n characters of string cs to string ct; return <0 if cs<ct, 0 if cs==ct, or >0 if cs>ct.
 from mac, "characters that appear after a `\0' character are not compared."


**/
int my_strncmp(const char *cs, const char *ct, size_t n) {
  const unsigned char *css, *ctt;
  assert(cs != NULL && ct != NULL);

  //for (css=cs, ctt=t; n-- > 0; css++, ctt++) //
  //  ;
  css = (const unsigned char *)cs;
  ctt = (const unsigned char *)ct;

  while (n-- > 0) {
    if(*css != *ctt || *css == '\0' || *ctt == '\0')
      return *css-*ctt;

    css++;
    ctt++;
  }

  return 0; // n==0, return 0 as if comparing two empty strings.
}

void test_strncmp(void) {
  int result;

  printf("test_strncmp\n");

  result = strncmp("abcd", "ab", 2);
  printf("Test 1. correct = %d, mine got = %d.\n", result, my_strncmp("abcd", "ab", 2));

  result = strncmp("abcd", "ab", 3);
  printf("Test 2. correct = %d, mine got = %d.\n", result, my_strncmp("abcd", "ab", 3));

  result = strncmp("abcd", "ab", 4);
  printf("Test 3. correct = %d, mine got = %d.\n", result, my_strncmp("abcd", "ab", 4));

  result = strncmp("ab", "abcd", 4);
  printf("Test 4. correct = %d, mine got = %d.\n", result, my_strncmp("ab", "abcd", 4));

  result = strncmp("abc", "abd", 3);
  printf("Test 5. correct = %d, mine got = %d.\n", result, my_strncmp("abc", "abd", 3));

  result = strncmp("abc", "abd", 4);
  printf("Test 6. correct = %d, mine got = %d.\n", result, my_strncmp("abc", "abd", 4));

  result = strncmp("abc", "abd", 2);
  printf("Test 7. correct = %d, mine got = %d.\n", result, my_strncmp("abc", "abd", 2));
  result = strncmp("abc", "ccc", 0);
  printf("Test 8. correct = %d, mine got = %d.\n", result, my_strncmp("abc", "ccc", 0)); // for n=0 always returns 0, i guess this is because its treated as a comparison of two empty strings.
}

int main(void) {
  printf("Exercise 5.5\n\n");
  test_strncmp();
  return 0;
}