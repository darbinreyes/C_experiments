#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAXLINES    5000
#define MAXLINESIZE 256

char **max(char **a, int len) {
  char **m;

  m = a;

  while(--len > 0) {
    a++;

    if(strcmp(*a, *m) > 0)//*a > *m)
      m = a;
  }

  return m;
}

void sort(char **a, int len) {
  char **tp;
  char *t;

  assert(a != NULL);

  if(len <= 0)
    return;

  while(--len > 0) {
    tp = max(a, len + 1);
    t = *a;
    *a = *tp;
    *tp = t;
    a++;
  }

  return;
}


// used by read lines
// from  /Users/darbinreyes/dev/experiments/C/KNR_C/Chapter5/s5.5/ce5.6.c
size_t my_getline(char *s,const int lim)
{
  char c;
  char *t;
  t=s;
  assert(lim != 0);
  while(s < (s+lim-1) && (c=getchar()) != EOF && c!='\n')
    *s++ = c;

  if(c == '\n')
    *s++ = c;

  *s = '\0';
  return (size_t)(s-t);
}

int readlines(char *lines[], int maxlines){
  int count = 0, i = 0;

  while(my_getline(*lines++, MAXLINESIZE) > 0 && maxlines > count++)
    ;

  return count;
}


// output lines
void writelines(char *lines[], int len) {

  assert(lines != NULL);
  int i = 0;

  while(len-- > 0)
    printf("%s", *lines++);
}
/**

Darbin-Reyess-MacBook-Pro:s5.5 darbinreyes$ echo 'a
b
c
'|./a.out
c
b
a

**/
int main(void) {
  int nlines = 0;
  char buffer[MAXLINES][MAXLINESIZE];
  char *bp[MAXLINES];

  while(nlines++ < MAXLINES)
    bp[nlines-1] = &buffer[nlines-1][0];


  nlines = readlines(bp, MAXLINES);

  sort(bp,nlines);


  writelines(bp, nlines);
}