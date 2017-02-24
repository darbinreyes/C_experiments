#include <stdio.h>
#include <stddef.h>

int main(void) {
  ptrdiff_t sub_p_q;
  int a[10];
  int *p;
  int *q;

  p=&a[0];
  q=&a[3];
  sub_p_q = q - p;
  // Question: is pointer subtraction scaled too? Yes.
  printf("hello, world. sizeof(int)=%lu, expect 4, p=%p, q=%p, p-q=%ld, expect 12, ptr_diff=%ld, expect 12.\n", sizeof(int), p, q, q-p, sub_p_q);
}