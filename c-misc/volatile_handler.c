#include <stdio.h>
int flag = 0;

void handler(int signum) {
    flag = 1; // Modified asynchronously
    printf("handled\n");
}