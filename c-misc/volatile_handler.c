#include <stdio.h>
int flag;

void handler(int signum) {
    flag = 1; // Modified asynchronously
    printf("handled\n");
}