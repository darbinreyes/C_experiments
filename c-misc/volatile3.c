#include <stdio.h>
#include <signal.h>
//volatile sig_atomic_t flag = 0; // volatile ensures compiler doesn't optimize reads/writes

void handler(int signum);

int main() {
    extern int flag;
    signal(SIGINT, handler);
    while (!flag) { // Compiler won't cache flag's value due to volatile
        // Work
        printf("working\n");
    }
    return 0;
}