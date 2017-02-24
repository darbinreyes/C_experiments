#include <stdio.h>
#include <stdlib.h>

void errmsg(void) {
  printf("Usage: ./detab -m +n. Tab stops every n cols starting at mth col.\n");
}

int get_m_n(int argc,char **argv, int *m, int *n){
  *m = -1;
  *n = -1;
  if(argc == 1) { // default is plane detab
    return -1;
  }

  if(argc == 3) {
    if(**++argv == '-' && (*m = atoi(++*argv)) > 0)
      ;

    if(**++argv == '+' && (*n = atoi(++*argv)) > 0)
      ;

    if(*m > 0 && *n > 0)
      return 0;
  }

  errmsg();
  return -1;
}

int main(int argc,char **argv) {
  int m, n;
  get_m_n(argc, argv, &m, &n);
  printf("m = %d. n = %d\n", m, n);
}