//my_binsearch_array
// My definition of a is sorted
 // i,j: (i < j) => (a[i] < a[j])


#include <stdio.h>
#include <assert.h>

unsigned int bsa(int a[], unsigned int n, int s) {
  assert(a != NULL);
  assert(n > 0);

  unsigned int f,m;
  f= 0;
  m = n/2;

  if(s == a[m])
    f = 1;
  else if (m > 0 && s < a[m])
    f = bsa(a+0, m, s);
  else if (m+1 < n && s > a[m])
    f = bsa(a+m+1, n-m-1, s);

  return f;
}


int main (int argc, char** argv) {
  int a[]={3};
  int b[]={3,5};
  int c[]={3,5,7};

  printf("Hello, world\n");
  printf("a={3}, s=3, f_e=1; f_c=%d\n", bsa(a,1,3));
  printf("a={3}, s=5, f_e=0; f_c=%d\n", bsa(a,1,5));

  printf("a={3,5}, s=3, f_e=1; f_c=%d\n", bsa(b,2,3));
  printf("a={3,5}, s=5, f_e=1; f_c=%d\n", bsa(b,2,5));

  printf("a={3,5}, s=7, f_e=0; f_c=%d\n", bsa(b,2,7));
  printf("a={3,5}, s=2, f_e=0; f_c=%d\n", bsa(b,2,2));

  printf("a={3,5,7}, s=5, f_e=1; f_c=%d\n", bsa(c,3,5));
  printf("a={3,5,7}, s=7, f_e=1; f_c=%d\n", bsa(c,3,7));
  printf("a={3,5,7}, s=3, f_e=1; f_c=%d\n", bsa(c,3,3));
  printf("a={3,5,7}, s=8, f_e=0; f_c=%d\n", bsa(c,3,8));

  return 0;
}