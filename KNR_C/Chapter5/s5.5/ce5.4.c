#include <stdio.h>
/**

Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t occurs at the
end of the string s, and zero otherwise.

**/
int strend(const char *s, const char *t) {
  const char *s_tmp, *t_tmp;

  if(s == NULL || t == NULL)
    return 0;

  if(*s == '\0' || *t == '\0')
    return 0; // don't match against NULL terminator. Treat as mismatch.

  // find first match in s, keep matching until hit null, else on mismatch, restart matching.

  while(*s != '\0') {
    s_tmp = s;
    t_tmp = t;

    while(*s_tmp == *t_tmp) {
      if(*s_tmp == '\0')
        return 1;

      s_tmp++;
      t_tmp++;
    }

    s++;
  }

  return 0;
}

int main(void) {
  printf("Exercise 5.4\n");

  // Tests, at least 2 tests per output.

  // expect 1.
  printf("strend(\"yaam\",\"am\") = %d, expect 1.\n", strend("yaam","am"));
  printf("strend(\"abc\",\"abc\") = %d, expect 1.\n", strend("abc","abc"));

  // expect 0


  printf("strend(\"abcde\",\"bc\") = %d, expect 0.\n", strend("abcde","bc"));
  printf("strend(\"abcbe\",\"bc\") = %d, expect 0.\n", strend("abcbe","bc"));

  // invalid args. expect 0.
  printf("strend(\"\",\"\") = %d, expect 0.\n", strend("",""));
  printf("strend(\"abc\",\"\") = %d, expect 0.\n", strend("abc",""));
  printf("strend(\"\",\"abc\") = %d, expect 0.\n", strend("","abc"));

  printf("strend(NULL,\"\") = %d, expect 0.\n", strend(NULL,""));

}