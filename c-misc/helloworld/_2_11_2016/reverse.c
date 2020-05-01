#include <stdio.h>
#include <assert.h>

// reverse a string in place.
// pre-condition: s is a null terminated string.
char *reverse(char *s) {
  char *end;
  char tmp;
  char *ss;

  // validate arg.s
  assert(s != NULL);

  //catch empty string
  if(*s == '\0')
    return s;

  // keep a pointer to the start so we can return it.
  ss = s;

  // find the end of the string.
  end = s; //init end to start

  // fast forward to end of string.
#if 0 // this might have the wrong operator precedence. I suspect this will increment the pointer first and then dereferece. Confirm this. // My suspicion was right, ref. K&R C page 95.
  while(*end++ != '\0')
    ;
#endif

  while(*end != '\0')
    end++;

  // rewind to last non-null char
  end--;

  // swap chars until you reach the center char. no need to swap after center.
  while(s < end) {
    tmp = *s;
    *s = *end;
    *end = tmp;
    s++;
    end--;
  }

  return ss;
}



// reverse() the string "hello" in main()

int main(int argc, char **argv) {
  printf("%s\n", argv[0]);

  if(argc > 1)
    printf("Arg1 = \"%s\"., Reversed = \"%s\".\n", argv[1], reverse(argv[1]) );
}

/**

Observations:

This program is O(n+n/2)= O(n). But if the reverse() function was given the length of the
string it could be written with O(n/2) time complexity.

// write a program that plays chess?

ispalindrome() is almost identical in code, you just need to replace the swap
with comparisons.
