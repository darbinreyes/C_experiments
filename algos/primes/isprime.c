#include <stdio.h>

int isprime(unsigned int n);

int main(void) {
  int i;
  printf("Hello, World\n");

  for(i=0;i <=102; i++) {
    if(isprime(i))
      printf("%d is prime.\n", i);
  }

  return 0;
}

// returns 1 if n is prime, 0 otherwise.
int isprime(unsigned int n) {
  int f;

  if(n==1||n==0)
    return 0;

  for(f=2; f*f <=n; f++) {
    if(n%f==0)
      return 0;
  }

  return 1;
}