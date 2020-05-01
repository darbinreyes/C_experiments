#include <stdio.h>



int *max(int a[], int len) {
  int *m;

  m = a;

  while(--len > 0) {
    a++;
    if(*a > *m)
      m = a;
  }

  return m;
}

void sort(int a[], int len) {
  int *tp;
  int t;

  if(len <= 0 || a == NULL)
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






int main(void) {
  int a[] = {3,2,3,1,4,1,43,12,31,0,-1};
  int len, i;

  len = sizeof(a)/sizeof(int);

  i = 0;
  while(i < len){
    printf(" %d ",a[i++]);
  }

  printf("\n");

  sort(a, len);
  i = 0;

  while(i < len){
    printf(" %d ", a[i++]);
  }

  printf("\n");

  return 0;
}