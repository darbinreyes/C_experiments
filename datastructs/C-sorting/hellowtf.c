
#include <stdio.h>

typedef void (*my_sort_func)(int a[], int len);

void shitty_sort(int a[], int len) { // sort little to big.
  int tmp_min;
  int tmp_min_index;
  int tmp;

  if(!a || len == 0)
    return;

  if(len == 1) // 1 elem. nothing to sort.
    return;

  tmp_min = a[0];
  tmp_min_index = 0;
  tmp = 0;

  for(int i = 0; i < len - 1; i++) {
    tmp_min = a[i];
    tmp_min_index = i;

    for(int j = i + 1; j < len; j++) {
      // scan the unsorted portion of the array a val smaller than a[i], if one is found,save its index too.
      if(a[j] < tmp_min) {
        tmp_min = a[j];
        tmp_min_index = j;
      }
    }

    if(tmp_min_index > i) { // smaller val was found. swap.
      tmp = a[i]; // save the val we are about to overwrite .
      a[i] = tmp_min;
      a[tmp_min_index] = tmp;
    }
  }

  return;
}

void printa(int a[], int len) {

  if(!a || len == 0)
    return;

  while(len--)
    printf("%d ", *a++);

  printf("\n");

  return;
}

void sort_test_0(my_sort_func sort_func) {
  //my_sort_func sort_func = shitty_sort;
  if(!sort_func)
    return;
  int a[] = {7,5,17,11,2,0,9};
  int len = sizeof(a)/sizeof(a[0]);
  printf("### %s sorting: ###\n", __FUNCTION__);

  printf("Before sorting:\n");
  printa(a, len);

  sort_func(a, len); // sort it.
  printf("After sorting:\n");
  printa(a, len);
}

int main(int argc, char *argv[]) {
  sort_test_0(shitty_sort);
  return 0;
}