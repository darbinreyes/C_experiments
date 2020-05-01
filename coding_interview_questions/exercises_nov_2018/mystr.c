#include <stdio.h> // printf()
#include <stdlib.h> //strlen()
#include <assert.h>
#include <string.h>
// https://hewlettpackard.github.io/ilo-rest-api-docs/ilo4/#example-use-cases
void reverse_str0(char *str) {
  assert(str != NULL);
  int l, s, e;
  char t;

  l = strlen(str);

  s = 0;
  e = l - 1;

  while (s < l / 2) {
    t = str[s];
    str[s] = str[e];
    str[e] = t;
    s++;
    e--;
  }
}

void reverse_str1(char *str) {
  assert(str != NULL);
  char t;
  char *end;
  end = str;

  if(*str == '\0') // handle empty string.
    return;

  while (*end != '\0')
    end++; //find end of the string.

  end--; // move backward from null terminator.

  while (str < end) {
    t = *str; // swap chars
    *str = *end;
    *end = t;
    str++; // update pointers.
    end--;
  }

}

int main(int argc, char **argv) {
  //char str[] = "yellow";
  char *str = argv[1];

  printf("str == %s\n", str);
  //reverse_str0(str);
  reverse_str1(str);
  printf("str == %s\n", str);

  return 0;
}