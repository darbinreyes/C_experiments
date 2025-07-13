#include <stdio.h>

int foo = 1;

int main(void) {
    int *fp;

    fp = &foo;

    while (*fp)
        ;

    printf("If you see this the compiler optimized out the loop guard.\n");
}