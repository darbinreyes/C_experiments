#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void foo(char ***c, int *rlen);

static char *s[] = {"hello", "my", "name", "is", "blah"};

int
main() {
  char **c;
  int len;
  int i;
  

  printf("hello, world\n");

  foo(&c, &len);

  printf("rlen = %d\n", len);

  for(i=0; i < len; i++){
  	printf("c[%d] = %s\n", i, c[i]);
  }
}


void foo(char ***c, int *rlen){
  int len;
  int i;

  len = sizeof(s)/sizeof(char *);

  printf("len = %d\n", len);
  *c = malloc(sizeof(char *)*len);

  *rlen = 0;

  for(i=0; i < len; i++){
  	printf("s[%d] = %s\n", *rlen, s[i]);

  	(*c)[*rlen] = strdup(s[i]);
  	(*rlen)++; /// results in a segmentation fault
  }


}