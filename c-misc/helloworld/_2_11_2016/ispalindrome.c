#include <stdio.h>
#include <assert.h>

// return true if s is a palindrome. false otherwise. An empty string is not a palindrome.
// pre-condition: s is a null terminated string.
int ispalindrome(char *s) {
  char *end;

  // validate arg.s
  assert(s != NULL);

  //catch empty string
  if(*s == '\0')
    return 0;

  // find the end of the string.
  end = s; //init end to start

  // fast forward to end of string.
  while(*end != '\0')
    end++;

  // rewind to last non-null char
  end--;

  // compare chars until you reach the center char. no need to compare center.
  while(s < end) {
    if(*s != *end)
      return 0; // mismatch, not palindrome.
    s++;
    end--;
  }

  return 1; // is palindrome!
}



// reverse() the string "hello" in main()

int main(int argc, char **argv) {
  printf("%s\n", argv[0]);

  if(argc > 1)
    printf("Arg1 = \"%s\"., ispalindrome = %d.\n", argv[1], ispalindrome(argv[1]) );
}

