#include <stdio.h>
#include <assert.h>

// return 0 if the given string is a palindrome,
int is_str_palindrome(char *str) {
  char *end;
  // assert str is null terminated.
  assert(str != NULL);
  assert(*str != '\0'); // reject empty string.

  // find end of the string;
  end = str;

  while (*end != '\0')
    end++;

  end--; // move back one char from the null terminator.

  // length 1 strings is always a palindrome.
  if ((end - str + 1) == 1)
    return 0;

  while (str < end) {
    // mismatch means the string is not a palindrome.
    if (*str != *end)
      return 1;

    str++;
    end--;

  }

  return 0;
}

int main(int argc, char **argv) {
  int r;

  printf("str = %s\n", argv[1]);
  r = is_str_palindrome(argv[1]);
  printf("is a palindrome = %s\n", (!r?  "yes": "no"));

  return 0;
}